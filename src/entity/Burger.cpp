#include "Burger.hpp"
#include "ingredient/BeefPatty.hpp"
#include "singleton/Collision.hpp"
#include "ingredient/IngredientImports.hpp"
#include <iostream>

entity::Burger::Burger(glm::vec3 position) : Entity(position, glm::vec3(0.09)) {
    ComputeHitBoxes();
    y_offset_ = this->GetHitBoxHeight();

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

    for (const std::unique_ptr<ingredient::Ingredient>& ing : this->ingredients_) {
        ing->Draw(c);
    }
}

void entity::Burger::AddIngredient(recipe::EIngredient index) {
    if (is_complete_) {
        //std::cout << "Still complete " << static_cast<int>(index) << '\n';
        return;
    }

    std::unique_ptr<ingredient::Ingredient> ingredient_ptr = GetIngredientByIndex(index);
    ingredient::Ingredient&                 ingredient    = *ingredient_ptr;

    ingredient.position_.y += y_offset_;
    this->y_offset_ += ingredient.GetHitBoxHeight();
    ingredient.rotation_.y += 255 * y_offset_;  // Aleatoriza a rotação do ingrediente no hamburger
    this->ingredients_.push_back(std::move(ingredient_ptr));

    is_complete_ = (index == recipe::EIngredient::TOPBUN);
}

std::unique_ptr<ingredient::Ingredient> entity::Burger::GetIngredientByIndex(recipe::EIngredient index) {
    using namespace recipe;

    switch (index) {
        case EIngredient::TOPBUN:
            return std::make_unique<ingredient::TopBun>(position_);

        case EIngredient::BOTTOMBUN:
            return std::make_unique<ingredient::BottomBun>(position_);

        case EIngredient::KETCHUP:
            return std::make_unique<ingredient::Ketchup>(position_);

        case EIngredient::MUSTARD:
            return std::make_unique<ingredient::Mustard>(position_);

        case EIngredient::BACON:
            return std::make_unique<ingredient::Bacon>(position_);

        case EIngredient::EGG:
            return std::make_unique<ingredient::Egg>(position_);

        case EIngredient::CHEESE:
            return std::make_unique<ingredient::Cheese>(position_);

        case EIngredient::LETTUCE:
            return std::make_unique<ingredient::Lettuce>(position_);

        case EIngredient::TOMATO:
            return std::make_unique<ingredient::Tomato>(position_);

        case EIngredient::BEEFPATTY:
            return std::make_unique<ingredient::BeefPatty>(position_);

        default:
            return std::make_unique<ingredient::Egg>(position_);
    }
}
