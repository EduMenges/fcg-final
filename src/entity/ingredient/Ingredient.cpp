#include "Ingredient.hpp"

ingredient::Ingredient::Ingredient(glm::vec3 position, glm::vec3 scale, recipe::EIngredient index)
    : Entity(position, scale), index_(index) {}
