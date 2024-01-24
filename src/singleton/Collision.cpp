#include "Collision.hpp"
#include <ranges>

void Collision::RemoveBox(HitBox* box) {
    auto result = std::ranges::find(boxes_, box);
    boxes_.erase(result);
}

void Collision::RemoveSphere(HitSphere* sphere) {
    auto result = std::ranges::find(spheres_, sphere);
    spheres_.erase(result);
}

bool HitBox::Colides(HitBox other) {
    return other.bbox_max_.x > bbox_min_.x && other.bbox_min_.x < bbox_max_.x &&  // Overlap in `x` plane
           other.bbox_max_.y > bbox_min_.y && other.bbox_min_.y < bbox_max_.y &&  // Overlap in `y` plane
           other.bbox_max_.z > bbox_min_.z && other.bbox_min_.z < bbox_max_.z;    // Overlap in `z` plane
}
