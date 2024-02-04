#pragma once

#include "entity/ingredient/Ingredient.hpp"
#include "entity/ingredient/IngredientImports.hpp"
#include "HeldObject.hpp"

class IngredientManager {
    public:
      using EntityContainer = std::list<std::unique_ptr<Entity>>;
      explicit IngredientManager(EntityContainer* ec, HeldObject* ho);
      EntityContainer* entities;
      HeldObject* held_object;

      void Init();
};