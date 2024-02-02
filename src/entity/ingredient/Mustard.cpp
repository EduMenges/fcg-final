#include "Mustard.hpp"
#include "singleton/Collision.hpp"

ingredient::Mustard::Mustard(glm::vec3 position) : Ingredient(position, glm::vec3(0.3)) {
    for (size_t i = 0; i < GetObj().bbox_min_.size(); ++i) {
        glm::vec3 bbox_min = GetObj().bbox_min_[i] * scale_;
        glm::vec3 bbox_max = GetObj().bbox_max_[i] * scale_;

        HitBox hb(bbox_min + position_, bbox_max + position_);
        AddHitBox(hb);
    }
}

void ingredient::Mustard::Update(double delta) {}

Obj& ingredient::Mustard::GetObj() {
    static Obj obj("../../../data/ingredients/mustard-splash.obj");
    return obj;
}