#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <algorithm>

class HitBox {
   public:
    constexpr HitBox(glm::vec3 bbox_min, glm::vec3 bbox_max) : bbox_min_(bbox_min), bbox_max_(bbox_max) {}

    [[nodiscard]] constexpr bool Collides(HitBox other) const {
        return other.bbox_max_.x > bbox_min_.x && other.bbox_min_.x < bbox_max_.x &&  // Overlap in `x` plane
               other.bbox_max_.y > bbox_min_.y && other.bbox_min_.y < bbox_max_.y &&  // Overlap in `y` plane
               other.bbox_max_.z > bbox_min_.z && other.bbox_min_.z < bbox_max_.z;    // Overlap in `z` plane
    }

    constexpr HitBox operator+(glm::vec3 pos) const { return {bbox_min_ + pos, bbox_max_ + pos}; }

   private:
    glm::vec3 bbox_min_;
    glm::vec3 bbox_max_;
};

class HitSphere {
   public:
    HitSphere(glm::vec3 center, float radius) : center_(center), radius_(radius) {}

   private:
    glm::vec3 center_;
    float     radius_;
};

class Collision {
   public:
    static Collision& Instance() {
        static Collision instance;
        return instance;
    }

    void AddBox(HitBox* box) { boxes_.push_back(box); }

    void AddSphere(HitSphere* sphere) { spheres_.push_back(sphere); }

    void RemoveBox(HitBox* box);

    void RemoveSphere(HitSphere* sphere);

    [[nodiscard]] constexpr bool ColidesWithBox(HitBox box) const {
        return std::ranges::any_of(boxes_, [&](auto other) { return box.Collides(*other); });
    }

   private:
    Collision() = default;

    std::vector<HitBox*>    boxes_;
    std::vector<HitSphere*> spheres_;
};
