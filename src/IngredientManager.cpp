#include "IngredientManager.hpp"
#include "entity/ingredient/BeefPatty.hpp"
#include "input/Mouse.hpp"
#include "singleton/Input.hpp"

IngredientManager::IngredientManager(EntityContainer* ec, HeldObject* ho) : entities_(ec), held_object_(ho) {}

void IngredientManager::Init() {
    entities_->emplace_back(std::make_unique<ingredient::Lettuce>(glm::vec3{2, 1.5, 3}));
    lettuce_ref = dynamic_cast<ingredient::Lettuce*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Egg>(glm::vec3{2, 1.5, 3.4}));
    egg_ref = dynamic_cast<ingredient::Egg*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Tomato>(glm::vec3{2, 1.5, 3.8}));
    tomato_ref = dynamic_cast<ingredient::Tomato*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Bacon>(glm::vec3{2, 1.5, 4.2}));
    bacon_ref = dynamic_cast<ingredient::Bacon*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Cheese>(glm::vec3{2, 1.5, 4.6}));
    cheese_ref = dynamic_cast<ingredient::Cheese*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::BeefPatty>(glm::vec3{2, 1.5, 5}));
    beef_ref = dynamic_cast<ingredient::BeefPatty*>(entities_->back().get());

}

void IngredientManager::Update(double delta) {
    input::Keys keys = Input::Instance().keys_;
    input::Mouse mouse = Input::Instance().mouse_;

    if (keys.IsOn(GLFW_KEY_1)) {
        held_object_->Set(*beef_ref);
    }

    if (keys.IsOn(GLFW_KEY_2)) {
        held_object_->Set(*tomato_ref);
    }
}
