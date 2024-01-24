#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <algorithm>

class HitBox {
   public:
    HitBox(glm::vec3 bbox_min, glm::vec3 bbox_max) : bbox_min_(bbox_min), bbox_max_(bbox_max) {}

    bool Colides(HitBox other);

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

    bool ColidesWithBox(HitBox box) {
        return std::ranges::any_of(boxes_, [&](auto other) { return box.Colides(*other); });
    }

   private:
    Collision() = default;

    std::vector<HitBox*>    boxes_;
    std::vector<HitSphere*> spheres_;
};
