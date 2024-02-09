#pragma once

#include "Entity.hpp"
#include "CubicBezier.hpp"
#include "Burger.hpp"

namespace entity {

class UFO : public Entity {
   public:
    explicit UFO(entity::Burger& burger);

    CubicBezier     bezier_;
    entity::Burger& burger_;
    HitSphere       sphere_{position_, 0.2};
    float           distance_to_burger;

    void Update(double delta) override;

    void Draw(Camera& c) override;

    Obj& GetObj() override;
};

}
