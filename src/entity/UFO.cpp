#include "UFO.hpp"

entity::UFO::UFO(entity::Burger& burger)
    : Entity(glm::vec3{burger.position_.x, 8, burger.position_.z}, glm::vec3{0.3}),
      burger_(burger),
      bezier_(burger.bezier_) {}

void entity::UFO::Update(double delta) {
    if (!burger_.is_correct_) {
        return;
    }

    if (!sphere_.CollidesWith(burger_.sphere_)) {
        position_.y -= delta;
        sphere_.SetCenter(position_);
    }

    else if (!burger_.is_traveling_) {
        burger_.is_traveling_ = true;
        distance_to_burger_   = position_.y - burger_.position_.y;
    }

    else {
        position_ = burger_.position_ + glm::vec3{0, distance_to_burger_, 0};
    }
}

void entity::UFO::Draw(Camera& c) { Model::Draw(c); }

Obj& entity::UFO::GetObj() {
    static Obj obj("../../../data/ufo/ufo.obj");
    return obj;
}
