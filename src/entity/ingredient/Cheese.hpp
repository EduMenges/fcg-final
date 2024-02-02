#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class Cheese : public Ingredient {
   public:
    explicit Cheese(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}