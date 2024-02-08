#include "IngredientManager.hpp"
#include "Camera.hpp"
#include "input/Mouse.hpp"
#include "singleton/Input.hpp"

IngredientManager::IngredientManager(EntityContainer* ec, HeldObject* ho) : entities_(ec), held_object_(ho) {}

void IngredientManager::Init() {
    entities_->emplace_back(std::make_unique<ingredient::Lettuce>(glm::vec3{1.2, table_y, -2}));  //
    lettuce_ref = dynamic_cast<ingredient::Lettuce*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Egg>(glm::vec3{-2, table_y, -0.7}));  //
    egg_ref = dynamic_cast<ingredient::Egg*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Tomato>(glm::vec3{-1.2, table_y, -2}));  //
    tomato_ref = dynamic_cast<ingredient::Tomato*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Bacon>(glm::vec3{2, table_y, -0.7}));  //
    bacon_ref = dynamic_cast<ingredient::Bacon*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Cheese>(glm::vec3{2, table_y, 0.7}));  //
    cheese_ref = dynamic_cast<ingredient::Cheese*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::BeefPatty>(glm::vec3{-2, table_y, 0.7}));  //
    beef_ref = dynamic_cast<ingredient::BeefPatty*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::TopBun>(glm::vec3{0, table_y, 2}));  //
    bun_ref = dynamic_cast<ingredient::TopBun*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::KetchupBottle>(glm::vec3{1.2, table_y, 2}));
    ketchup_ref              = dynamic_cast<ingredient::KetchupBottle*>(entities_->back().get());
    ketchup_ref->rotation_.y = glm::radians(180.0F);

    entities_->emplace_back(std::make_unique<ingredient::MustardBottle>(glm::vec3{-1.2, table_y, 2}));
    mustard_ref              = dynamic_cast<ingredient::MustardBottle*>(entities_->back().get());
    mustard_ref->rotation_.y = glm::radians(180.0F);
}

void IngredientManager::Update(double delta) {
    const std::array<ingredient::Ingredient*, kIngredientAmount> kIngredients{
        lettuce_ref, egg_ref,    tomato_ref, bacon_ref,   cheese_ref,
        beef_ref,    cheese_ref, bun_ref,    ketchup_ref, mustard_ref};

    input::Mouse mouse = Input::Instance().mouse_;

    bool grab = Input::Instance().IsOn(GLFW_KEY_E);

    const bool kInteracted         = mouse.M1 || grab;
    const bool kNotHoldingAnything = held_object_->object_ == nullptr;

    for (auto ingredient : kIngredients) {
        Camera& camera = *(held_object_->camera);

        if (ingredient->IsBeingLooked(camera)) {
            ingredient->rotation_.y += delta;
            if (kNotHoldingAnything && kInteracted) {
                held_object_->Set(*ingredient);
            }
        }
    }
}
