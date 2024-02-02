#include "BottomBun.hpp"
#include "singleton/Collision.hpp"

ingredient::BottomBun::BottomBun(glm::vec3 position) : Ingredient(position, glm::vec3(0.3)) {
    for (size_t i = 0; i < GetObj().bbox_min_.size(); ++i) {
        glm::vec3 bbox_min = GetObj().bbox_min_[i] * scale_;
        glm::vec3 bbox_max = GetObj().bbox_max_[i] * scale_;

        HitBox hb(bbox_min + position_, bbox_max + position_);
        AddHitBox(hb);
    }
}

void ingredient::BottomBun::Update(double delta) {}

Obj& ingredient::BottomBun::GetObj() {
    static Obj obj("../../../data/ingredients/bottom_bun.obj");
    return obj;
}