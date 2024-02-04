#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class BeefPatty : public Ingredient {
   public:
    explicit BeefPatty(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}