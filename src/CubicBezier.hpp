#pragma once

#include <array>
#include "trait/Updatable.hpp"
#include "glm/glm.hpp"

class CubicBezier : public trait::Updatable {
   public:
    enum class Direction : uint8_t { kForward, kBackward };

    constexpr CubicBezier(std::array<glm::vec3, 4> points, double duration, bool loop = true)
        : points_(points), duration_(duration), loop_(loop) {}

    void Update(double delta) override;

    [[nodiscard]] glm::vec3 Get() const;

   private:
    std::array<glm::vec3, 4> points_;

    /// How long the curve animation lasts
    double duration_;

    /// Should the animation go on a loop, that is, bo backwards once it has ended
    bool loop_ = true;

    /// Current animation timer, how much has it progressed
    double timer_ = 0.0;

    Direction direction_ = Direction::kForward;
};
