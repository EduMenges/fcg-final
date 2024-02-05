#include "Collision.hpp"
#include <ranges>

void Collision::RemoveBox(HitBox* box) {
    if (auto result = std::ranges::find(boxes_, box); result != std::ranges::end(boxes_)) {
        boxes_.erase(result);
    }
}

void Collision::RemoveSphere(HitSphere* sphere) {
    auto result = std::ranges::find(spheres_, sphere);
    spheres_.erase(result);
}
