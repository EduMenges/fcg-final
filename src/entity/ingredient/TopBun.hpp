#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class TopBun : public Ingredient {
   public:
    explicit TopBun(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}