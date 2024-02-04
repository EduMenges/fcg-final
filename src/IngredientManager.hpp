#pragma once

#include "entity/ingredient/Ingredient.hpp"
#include "entity/ingredient/IngredientImports.hpp"

class IngredientManager {
    public:
      using EntityContainer = std::list<std::unique_ptr<Entity>>;
      explicit IngredientManager(EntityContainer* ec);
      EntityContainer* entities;
};