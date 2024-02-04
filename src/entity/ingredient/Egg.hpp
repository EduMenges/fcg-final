#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class Egg : public Ingredient {
   public:
    explicit Egg(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}