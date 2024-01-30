#include "KetchupBottle.hpp"
#include "singleton/Collision.hpp"

entity::KetchupBottle::KetchupBottle(glm::vec3 position) : Entity(position, glm::vec3(0.2)) {
    for (size_t i = 0; i < GetObj().bbox_min_.size(); ++i) {
        glm::vec3 bbox_min = GetObj().bbox_min_[i] * scale_;
        glm::vec3 bbox_max = GetObj().bbox_max_[i] * scale_;

        HitBox hb(bbox_min + position_, bbox_max + position_);
        AddHitBox(hb);
    }
}

void entity::KetchupBottle::Update(double delta) { /* rotation_.y += static_cast<float>(delta); */ }

Obj& entity::KetchupBottle::GetObj() {
    static Obj obj("../../../data/condiments/ketchup.obj");
    return obj;
}
