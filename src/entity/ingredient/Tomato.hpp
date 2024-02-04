#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class Tomato : public Ingredient {
   public:
    explicit Tomato(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}