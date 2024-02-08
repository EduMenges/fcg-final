#include "UFO.hpp"

entity::UFO::UFO(entity::Burger& burger) : Entity(glm::vec3{burger.position_.x, 9, burger.position_.z}, glm::vec3{0.1}), burger_(burger), bezier_(burger.bezier_) {}


void entity::UFO::Update(double delta) {
    if(!sphere_.CollidesWith(burger_.sphere_) && burger_.is_correct_) {
        position_.y -= delta;
        sphere_.SetCenter(position_);
    }
}

void entity::UFO::Draw(Camera& c) {
    Model::Draw(c);
}

Obj& entity::UFO::GetObj() {
    static Obj obj("../../../data/ingredients/mustard-splash.obj");
    return obj;
}