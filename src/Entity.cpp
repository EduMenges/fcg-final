#include "Entity.hpp"

Entity::~Entity() {
    for (HitBox& hit_box: hit_boxes_) {
        Collision::Instance().RemoveBox(&hit_box);
    }
}

void Entity::AddHitBox(HitBox hb) {
    auto& location = hit_boxes_.emplace_back(hb);
    Collision::Instance().AddBox(&location);
}

void Entity::ComputeHitBoxes() {
    for (size_t i = 0; i < GetObj().bbox_min_.size(); ++i) {
        glm::vec3 bbox_min = GetObj().bbox_min_[i] * scale_;
        glm::vec3 bbox_max = GetObj().bbox_max_[i] * scale_;

        HitBox hb(bbox_min + position_, bbox_max + position_);
        AddHitBox(hb);
    }
}
