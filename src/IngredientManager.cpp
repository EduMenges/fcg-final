#include "IngredientManager.hpp"

IngredientManager::IngredientManager(EntityContainer* ec, HeldObject* ho): entities(ec), held_object(ho) {}

void IngredientManager::Init() {

    std::unique_ptr<ingredient::Lettuce> lettuce = std::make_unique<ingredient::Lettuce>(glm::vec3{2, 1.5, 3});
    entities->emplace_back(std::move(lettuce));
    ingredient::Lettuce* lettuce_ref = dynamic_cast<ingredient::Lettuce*>(entities->back().get());

    std::unique_ptr<ingredient::Egg> egg = std::make_unique<ingredient::Egg>(glm::vec3{2, 1.5, 3.4});
    entities->emplace_back(std::move(egg));
    ingredient::Egg* egg_ref = dynamic_cast<ingredient::Egg*>(entities->back().get());

    held_object->Set(*egg_ref);
}