#pragma once
#include "Entity.hpp"
#include "recipe/EIngredient.hpp"

namespace ingredient{
    class Ingredient: public Entity {
        public:
          explicit Ingredient(glm::vec3 position, glm::vec3 scale);
          //const recipe::EIngredient index;
    };
}