#pragma once

#include "Entity.hpp"
#include "recipe/EIngredient.hpp"

namespace ingredient {
class Ingredient : public Entity {
   public:
    explicit Ingredient(glm::vec3 position, glm::vec3 scale, recipe::EIngredient index = recipe::EIngredient::kCount);

    recipe::EIngredient index_;
};
}
