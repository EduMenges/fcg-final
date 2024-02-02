#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class BottomBun : public Ingredient {
   public:
    explicit BottomBun(glm::vec3 position);
    const recipe::EIngredient index = recipe::EIngredient::BOTTOMBUN;

    void Update(double delta) override;

    Obj& GetObj() override;
};

}