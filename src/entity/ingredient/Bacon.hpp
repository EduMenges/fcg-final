#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class Bacon : public Ingredient {
   public:
    explicit Bacon(glm::vec3 position);
    recipe::EIngredient index = recipe::EIngredient::BACON;

    void Update(double delta) override;

    Obj& GetObj() override;
};

}