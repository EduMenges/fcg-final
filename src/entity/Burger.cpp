#include "Burger.hpp"
#include "ingredient/Bacon.hpp"
#include "ingredient/BottomBun.hpp"
#include "ingredient/Cheese.hpp"
#include "ingredient/Egg.hpp"
#include "ingredient/Ingredient.hpp"
#include "ingredient/Ketchup.hpp"
#include "ingredient/Lettuce.hpp"
#include "ingredient/Mustard.hpp"
#include "singleton/Collision.hpp"
#include "ingredient/IngredientImports.hpp"

entity::Burger::Burger(glm::vec3 position) : Entity(position, glm::vec3(0.09)), isComplete(false) {
    ComputeHitBoxes();
    yOffset = this->GetHitboxHeight();

    AddIngredient(recipe::EIngredient::BOTTOMBUN);
    AddIngredient(recipe::EIngredient::LETTUCE);
    AddIngredient(recipe::EIngredient::BACON);
    AddIngredient(recipe::EIngredient::EGG);
    AddIngredient(recipe::EIngredient::TOPBUN);
    
    //this->ingredients.push_back(std::make_unique<ingredient::Egg>(position+glm::vec3{0, .25, 0}));
    //this->ingredients.push_back(std::make_unique<ingredient::Mustard>(position+glm::vec3{0, .5, 0}));
}

void entity::Burger::Update(double delta) {
    rotation_.y += static_cast<float>(delta); 
    for(const std::unique_ptr<ingredient::Ingredient>& ing : this->ingredients)
        ing->rotation_.y = rotation_.y;
    }

Obj& entity::Burger::GetObj() {
    static Obj obj("../../../data/kitchenware/plate.obj");
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
    using namespace recipe;

    switch (index) {
        case EIngredient::TOPBUN:
            return std::make_unique<ingredient::TopBun>(position_); 
            break;

        case EIngredient::BOTTOMBUN:
            //yOffset -= 0.025;
            return std::make_unique<ingredient::BottomBun>(position_); 
            break;

        case EIngredient::KETCHUP:
            return std::make_unique<ingredient::Ketchup>(position_); 
            break;

        case EIngredient::MUSTARD:
            return std::make_unique<ingredient::Mustard>(position_); 
            break;

        case EIngredient::BACON:
            return std::make_unique<ingredient::Bacon>(position_); 
            break;

        case EIngredient::EGG:
            return std::make_unique<ingredient::Egg>(position_); 
            break;

        case EIngredient::CHEESE:
            return std::make_unique<ingredient::Cheese>(position_); 
            break;

        case EIngredient::LETTUCE:
            return std::make_unique<ingredient::Lettuce>(position_); 
            break;

    
    }

}