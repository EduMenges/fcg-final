#include "IngredientManager.hpp"
#include "entity/ingredient/BeefPatty.hpp"

IngredientManager::IngredientManager(EntityContainer* ec, HeldObject* ho): entities(ec), held_object(ho) {}

void IngredientManager::Init() {

    std::unique_ptr<ingredient::Lettuce> lettuce = std::make_unique<ingredient::Lettuce>(glm::vec3{2, 1.5, 3});
    entities->emplace_back(std::move(lettuce));
    lettuce_ref = dynamic_cast<ingredient::Lettuce*>(entities->back().get());

    std::unique_ptr<ingredient::Egg> egg = std::make_unique<ingredient::Egg>(glm::vec3{2, 1.5, 3.4});
    entities->emplace_back(std::move(egg));
    egg_ref = dynamic_cast<ingredient::Egg*>(entities->back().get());

    std::unique_ptr<ingredient::Tomato> tomato = std::make_unique<ingredient::Tomato>(glm::vec3{2, 1.5, 3.8});
    entities->emplace_back(std::move(tomato));
    tomato_ref = dynamic_cast<ingredient::Tomato*>(entities->back().get());

    std::unique_ptr<ingredient::Bacon> bacon = std::make_unique<ingredient::Bacon>(glm::vec3{2, 1.5, 4.2});
    entities->emplace_back(std::move(bacon));
    bacon_ref = dynamic_cast<ingredient::Bacon*>(entities->back().get());

    std::unique_ptr<ingredient::Cheese> cheese = std::make_unique<ingredient::Cheese>(glm::vec3{2, 1.5, 4.6});
    entities->emplace_back(std::move(cheese));
    cheese_ref = dynamic_cast<ingredient::Cheese*>(entities->back().get());

    std::unique_ptr<ingredient::BeefPatty> beef = std::make_unique<ingredient::BeefPatty>(glm::vec3{2, 1.5, 5});
    entities->emplace_back(std::move(beef));
    beef_ref = dynamic_cast<ingredient::BeefPatty*>(entities->back().get()); 

    //held_object->Set(*egg_ref);
}

void IngredientManager::Update(double delta) {
    input::Keys keys = Input::Instance().keys_;

    if(keys.IsOn(GLFW_KEY_1)){
        held_object->Set(*beef_ref);
    }

    if(keys.IsOn(GLFW_KEY_2)){
        held_object->Set(*tomato_ref);
    }
}