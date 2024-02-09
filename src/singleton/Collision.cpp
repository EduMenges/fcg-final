#include "Collision.hpp"
#include <ranges>
#include "matrices.hpp"

void Collision::RemoveBox(HitBox* box) {
    if (auto result = std::ranges::find(boxes_, box); result != std::ranges::end(boxes_)) {
        boxes_.erase(result);
    }
}

void Collision::RemoveSphere(HitSphere* sphere) {
    if (auto result = std::ranges::find(spheres_, sphere); result != std::ranges::end(spheres_)) {
        spheres_.erase(result);
    }
}

bool HitSphere::CollidesWith(HitSphere sph2) {
    glm::vec3 to_center       = sph2.GetCenter() - center_;
    float     center_distance = Norm(to_center);
    return center_distance <= radius_ + sph2.GetRadius();
}
