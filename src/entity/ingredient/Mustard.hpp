#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class Mustard : public Ingredient {
   public:
    explicit Mustard(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}
