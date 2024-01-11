#pragma once

#include "glm/glm.hpp"
#include "user_input/Keys.hpp"

class Camera {
   public:
    Camera() = default;
   private:
    /// Where the camera is located, in cartesian coordinates.
    glm::vec4 position_ = {0.4F, 0.8F, 0.0F, 1.0F};

    float nearPlane_ = -0.1F;
    float farPlane_ = -100.0F;

    /// Orientation as to where the camera is pointing to.
    glm::vec4 viewVector_;

    /// Keyboard control variables.
    Keys keys_;
};
