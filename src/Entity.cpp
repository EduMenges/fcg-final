#include "Entity.hpp"

Entity::~Entity() {
    for (HitBox& hit_box: hit_boxes_) {
        Collision::Instance().RemoveBox(&hit_box);
    }
}
