#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class BottomBun : public Ingredient {
   public:
    explicit BottomBun(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}