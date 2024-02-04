#pragma once

#include "entity/ingredient/Ingredient.hpp"
#include "entity/ingredient/IngredientImports.hpp"
#include "HeldObject.hpp"
#include "input/Keys.hpp"
#include "singleton/Input.hpp"

class IngredientManager {
    public:
      using EntityContainer = std::list<std::unique_ptr<Entity>>;
      explicit IngredientManager(EntityContainer* ec, HeldObject* ho);
      EntityContainer* entities;
      HeldObject* held_object;

      ingredient::Lettuce* lettuce_ref;
      ingredient::Egg* egg_ref;
      ingredient::Tomato* tomato_ref;

      void Init();

      void Update(double delta);
};