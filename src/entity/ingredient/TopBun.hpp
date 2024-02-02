#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class TopBun : public Ingredient {
   public:
    explicit TopBun(glm::vec3 position);
    const recipe::EIngredient index = recipe::EIngredient::TOPBUN;

    void Update(double delta) override;

    Obj& GetObj() override;
};

}