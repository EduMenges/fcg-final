#pragma once

#include <glm/ext/vector_double2.hpp>
#include "Action.hpp"
#include "fmt/core.h"

namespace input {
class Mouse {
   public:
    Mouse() = default;

    void TakeAction(int button, Action action);

    void SetPos(double xpos, double ypos) {
        last_x = std::exchange(x, xpos);
        last_y = std::exchange(y, ypos);
    }

    [[nodiscard]] glm::dvec2 GetDelta() const { return {x - last_x, y - last_y}; }

    bool M1 = false;
    bool M2 = false;

   private:
    double x = 0.0;
    double y = 0.0;

    double last_x = 0.0;
    double last_y = 0.0;
};
}
