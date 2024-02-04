#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class Tomato : public Ingredient {
   public:
    explicit Tomato(glm::vec3 position);
    recipe::EIngredient index = recipe::EIngredient::TOMATO;

    void Update(double delta) override;

    Obj& GetObj() override;
};

}