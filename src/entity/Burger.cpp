#include "Burger.hpp"
#include "singleton/Collision.hpp"
#include "ingredient/IngredientImports.hpp"

entity::Burger::Burger(glm::vec3 position) : Entity(position, glm::vec3(0.09)), isComplete(false) {
    ComputeHitBoxes();
    yOffset = this->GetHitBoxHeight();

    AddIngredient(recipe::EIngredient::BOTTOMBUN);

}

void entity::Burger::Update(double delta) {
    /* float dy = static_cast<float>(delta);
    rotation_.y += dy; 
    for(const std::unique_ptr<ingredient::Ingredient>& ing : this->ingredients)
        ing->rotation_.y += dy; */
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
    ingredient.position_.y += yOffset;
    this->yOffset += ingredient.GetHitBoxHeight();
    ingredient.rotation_.y += 255*yOffset; // Aleatoriza a rotação do ingrediente no hamburger
    this->ingredients.push_back(std::move(ingredientPtr));
}

std::unique_ptr<ingredient::Ingredient> entity::Burger::GetIngredientByIndex(recipe::EIngredient index) {
    using namespace recipe;

    switch (index) {
        case EIngredient::TOPBUN:
            return std::make_unique<ingredient::TopBun>(position_); 
            break;

        case EIngredient::BOTTOMBUN:
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

        case EIngredient::TOMATO:
            return std::make_unique<ingredient::Tomato>(position_); 
            break;

    
    }

}