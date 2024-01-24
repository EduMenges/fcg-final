#pragma once

#include <vector>

#include "collision/HitBox.hpp"
#include "collision/HitSphere.hpp"

class Collision {
   public:
    static Collision& Instance() {
        static Collision instance;
        return instance;
    }

    void AddBox(collision::HitBox* box) {
        boxes_.push_back(box);
    }

    void AddSphere(collision::HitSphere* sphere) {
        spheres_.push_back(sphere);
    }

    void RemoveBox(collision::HitBox* box);

    void RemoveSphere(collision::HitSphere* sphere);

   private:
    Collision() = default;

    std::vector<collision::HitBox*> boxes_;
    std::vector<collision::HitSphere*> spheres_;
};
