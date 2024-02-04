#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class Ketchup : public Ingredient {
   public:
    explicit Ketchup(glm::vec3 position);
    recipe::EIngredient index = recipe::EIngredient::KETCHUP;

    void Update(double delta) override;

    Obj& GetObj() override;
};

}