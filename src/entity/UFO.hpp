#pragma once

#include "Entity.hpp"
#include "CubicBezier.hpp"
#include "Burger.hpp"

namespace entity {

class UFO : public Entity {
   public:
    explicit UFO(entity::Burger& burger);
    

    CubicBezier bezier_;
    entity::Burger& burger_;
    float distance_from_burger;
    HitSphere sphere_{position_, 0.2};

    void Update(double delta) override;

    void Draw(Camera& c) override;

    Obj& GetObj() override;

};

}
