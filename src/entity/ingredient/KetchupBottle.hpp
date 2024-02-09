#pragma once
#include "Ingredient.hpp"

namespace ingredient {

class KetchupBottle : public Ingredient {
   public:
    explicit KetchupBottle(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}
