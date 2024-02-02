#include "CubicBezier.hpp"

void CubicBezier::Update(double delta) {
    switch (direction_) {
        case Direction::kForward:
            timer_ += delta;
            break;
        case Direction::kBackward:
            timer_ -= delta;
    }

    if (timer_ > duration_) {
        if (loop_) {
            timer_     = duration_;
            direction_ = Direction::kBackward;
        } else {
            timer_ = 0.0;
        }
        return;
    }

    if (timer_ <= 0.0) {
        if (loop_) {
            timer_     = 0.0;
            direction_ = Direction::kForward;
        } else {
            timer_ = 0.0;
        }
    }
}

glm::vec3 CubicBezier::Get() const {
    auto  t = static_cast<float>(timer_ / duration_);  // Time elapsed as percentage
    float r = 1.0F - t;                                // Remaining time

    return std::pow(r, 3.0F) * points_[0] +             // b 0,3
           3.0F * t * std::pow(r, 2.0F) * points_[1] +  // b 1,3
           3.0F * std::pow(t, 2.0F) * r * points_[2] +  // b 2,3
           std::pow(t, 3.0F) * points_[3];              // b 3,3
}
