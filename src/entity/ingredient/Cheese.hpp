#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class Cheese : public Ingredient {
   public:
    explicit Cheese(glm::vec3 position);
    const recipe::EIngredient index = recipe::EIngredient::CHEESE;

    void Update(double delta) override;

    Obj& GetObj() override;
};

}