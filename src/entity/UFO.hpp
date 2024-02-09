#pragma once

#include "Entity.hpp"
#include "CubicBezier.hpp"
#include "Burger.hpp"

namespace entity {

class UFO : public Entity {
   public:
    explicit UFO(entity::Burger& burger);

    entity::Burger& burger_;
    CubicBezier     bezier_;
    HitSphere       sphere_{position_, 0.2F};
    float           distance_to_burger_;

    void Update(double delta) override;

    void Draw(Camera& c) override;

    Obj& GetObj() override;
};

}
