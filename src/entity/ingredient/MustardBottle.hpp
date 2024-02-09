#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class MustardBottle : public Ingredient {
   public:
    explicit MustardBottle(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}
