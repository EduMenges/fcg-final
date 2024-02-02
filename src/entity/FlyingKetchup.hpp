#pragma once

#include "Entity.hpp"
#include "CubicBezier.hpp"

namespace entity {
class FlyingKetchup : public Entity {
   public:
    FlyingKetchup() : Entity({2.0F, 1.0F, 1.0F}){};

    void Update(double delta) override;
    Obj& GetObj() override;

   private:
    CubicBezier bezier_{{glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 2.0, 0.0), glm::vec3(1.5, 3.0, 1.0), {1.0, 4.0, 1.5}},
                        5.0};
};
}
