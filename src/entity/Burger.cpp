#include "Burger.hpp"
#include "ingredient/BeefPatty.hpp"
#include "singleton/Collision.hpp"
#include "ingredient/IngredientImports.hpp"
#include <iostream>

entity::Burger::Burger(glm::vec3 position) : Entity(position, glm::vec3(0.09)) {
    ComputeHitBoxes();
    y_offset_ = this->GetHitBoxHeight();

    AddIngredient(recipe::EIngredient::kBottomBun);
}

void entity::Burger::Update(double delta) {
    if (!is_correct_ || position_.z > 7.0F || !is_traveling_) {
        return;
    }

    auto dy = static_cast<float>(delta);
    bezier_.Update(delta);
    glm::vec3 adjustment = bezier_.Get() - position_;

    rotation_.y += 8 * dy;
    position_ += adjustment;

    for (auto& ing : this->ingredients_) {
        ing->rotation_.y += 8.0F * dy;
        ing->position_ += adjustment;
    }
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
        return;
    }

    std::unique_ptr<ingredient::Ingredient> ingredient_ptr = GetIngredientByIndex(index);
    ingredient::Ingredient&                 ingredient     = *ingredient_ptr;

    ingredient.position_.y += y_offset_;
    this->y_offset_ += ingredient.GetHitBoxHeight();
    sphere_.AddToRadius(ingredient.GetHitBoxHeight());
    ingredient.rotation_.y += 255 * y_offset_;  // Aleatoriza a rotação do ingrediente no hamburger
    this->ingredients_.push_back(std::move(ingredient_ptr));

    is_complete_ = (index == recipe::EIngredient::kTopBun);
}

std::unique_ptr<ingredient::Ingredient> entity::Burger::GetIngredientByIndex(recipe::EIngredient index) {
    using namespace recipe;

    switch (index) {
        case EIngredient::kTopBun:
            return std::make_unique<ingredient::TopBun>(position_);

        case EIngredient::kBottomBun:
            return std::make_unique<ingredient::BottomBun>(position_);

        case EIngredient::kKetchup:
            return std::make_unique<ingredient::Ketchup>(position_);

        case EIngredient::kMustard:
            return std::make_unique<ingredient::Mustard>(position_);

        case EIngredient::kBacon:
            return std::make_unique<ingredient::Bacon>(position_);

        case EIngredient::kEgg:
            return std::make_unique<ingredient::Egg>(position_);

        case EIngredient::kCheese:
            return std::make_unique<ingredient::Cheese>(position_);

        case EIngredient::kLettuce:
            return std::make_unique<ingredient::Lettuce>(position_);

        case EIngredient::kTomato:
            return std::make_unique<ingredient::Tomato>(position_);

        case EIngredient::kBeefPatty:
            return std::make_unique<ingredient::BeefPatty>(position_);
        default:
            return std::make_unique<ingredient::Egg>(position_);
    }
}
