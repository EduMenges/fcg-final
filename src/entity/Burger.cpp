#include "Burger.hpp"
#include "ingredient/Ingredient.hpp"
#include "singleton/Collision.hpp"
#include "ingredient/Egg.hpp"
#include "ingredient/Cheese.hpp"
#include "ingredient/Mustard.hpp"

entity::Burger::Burger(glm::vec3 position) : Entity(position, glm::vec3(0.1)), isComplete(false) {
    ComputeHitBoxes();
    yOffset = this->GetHitboxHeight();
    AddIngredient(recipe::EIngredient::EGG);
    AddIngredient(recipe::EIngredient::CHEESE);
    //this->ingredients.push_back(std::make_unique<ingredient::Egg>(position+glm::vec3{0, .25, 0}));
    //this->ingredients.push_back(std::make_unique<ingredient::Mustard>(position+glm::vec3{0, .5, 0}));
}

void entity::Burger::Update(double delta) {
    rotation_.y += static_cast<float>(delta); 
    for(const std::unique_ptr<ingredient::Ingredient>& ing : this->ingredients)
        ing->rotation_.y = rotation_.y;
    }

Obj& entity::Burger::GetObj() {
    static Obj obj("../../../data/ingredients/ketchup-splash.obj");
    return obj;
}

void entity::Burger::Draw(Camera& c) {
    Model::Draw(c);
    for(const std::unique_ptr<ingredient::Ingredient>& ing : this->ingredients)
        ing->Draw(c);
}

void entity::Burger::AddIngredient(recipe::EIngredient index) {
    std::unique_ptr<ingredient::Ingredient> ingredientPtr = GetIngredientByIndex(index);
    ingredient::Ingredient& ingredient = *ingredientPtr;
    ingredient.position_ += glm::vec3(0,yOffset,0);
    this->yOffset += ingredient.GetHitboxHeight();
    this->ingredients.push_back(std::move(ingredientPtr));
}

std::unique_ptr<ingredient::Ingredient> entity::Burger::GetIngredientByIndex(recipe::EIngredient index) {
    if(index == recipe::EIngredient::EGG)
        return std::make_unique<ingredient::Egg>(position_); 
    else
        return std::make_unique<ingredient::Cheese>(position_);
}