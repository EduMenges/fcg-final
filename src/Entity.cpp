//
// Created by menges on 1/14/24.
//

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
