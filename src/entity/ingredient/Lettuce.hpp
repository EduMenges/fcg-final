#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class Lettuce : public Ingredient {
   public:
    explicit Lettuce(glm::vec3 position);
    const recipe::EIngredient index = recipe::EIngredient::LETTUCE;

    void Update(double delta) override;

    Obj& GetObj() override;
};

}