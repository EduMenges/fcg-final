#include "Bacon.hpp"
#include "singleton/Collision.hpp"

ingredient::Bacon::Bacon(glm::vec3 position) : Ingredient(position, glm::vec3(0.3)) {
    for (size_t i = 0; i < GetObj().bbox_min_.size(); ++i) {
        glm::vec3 bbox_min = GetObj().bbox_min_[i] * scale_;
        glm::vec3 bbox_max = GetObj().bbox_max_[i] * scale_;

        HitBox hb(bbox_min + position_, bbox_max + position_);
        AddHitBox(hb);
    }
}

void ingredient::Bacon::Update(double delta) {}

Obj& ingredient::Bacon::GetObj() {
    static Obj obj("../../../data/ingredients/ketchup-splash.obj");
    return obj;
}