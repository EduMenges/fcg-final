#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

class HitBox {
   public:
    constexpr HitBox(glm::vec3 bbox_min, glm::vec3 bbox_max) : min_(bbox_min), max_(bbox_max) {}

    [[nodiscard]] constexpr bool Collides(HitBox other) const {
        return other.max_.x > min_.x && other.min_.x < max_.x &&  // Overlap in `x` plane
               other.max_.y > min_.y && other.min_.y < max_.y &&  // Overlap in `y` plane
               other.max_.z > min_.z && other.min_.z < max_.z;    // Overlap in `z` plane
    }

    constexpr void AdjustValues() {
        glm::vec3 new_min{std::min(min_.x, max_.x), std::min(min_.y, max_.y), std::min(min_.z, max_.z)};
        glm::vec3 new_max{std::max(min_.x, max_.x), std::max(min_.y, max_.y), std::max(min_.z, max_.z)};

        min_ = new_min;
        max_ = new_max;
    }

    constexpr HitBox operator+(glm::vec3 pos) const { return {min_ + pos, max_ + pos}; }

    constexpr HitBox operator*(glm::vec3 scale) const { return {min_ * scale, max_ * scale}; }

    glm::vec3 min_;
    glm::vec3 max_;
};

class HitSphere {
   public:
    HitSphere(glm::vec3 center, float radius) : center_(center), radius_(radius) {}

    void                AddToRadius(float dr) { radius_ += dr; }
    glm::vec3           GetCenter() { return center_; }
    [[nodiscard]] float GetRadius() const { return radius_; }

    bool CollidesWith(HitSphere sph2);

    void SetCenter(glm::vec3 center) { center_ = center; }

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
