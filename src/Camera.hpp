#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "matrices.hpp"

class Camera {
public:
    Camera()          = default;
    virtual ~Camera() = default;

    virtual glm::mat4 GetMatrix();

    virtual glm::vec4 GetViewVec() = 0;

    float rot_x_{0};
    float rot_y_{0};

protected:
    static constexpr glm::vec4 kUp{0.0F, 1.0F, 0.0F, 0.0F};

    virtual glm::vec4 GetCenter() = 0;
};

class LookAtCamera : public Camera {
public:
    explicit LookAtCamera(glm::vec3 look_at) : look_at_(look_at) {}

    glm::vec4 GetViewVec() override;

    glm::vec3 look_at_;
    float     distance_ = 3.5F;

private:
    glm::vec4 GetCenter() override;
};

class FreeCamera : public Camera {
public:
    glm::vec4 GetViewVec() override;

    glm::vec3 position_ = glm::vec3(0);

private:
    glm::vec4 GetCenter() override { return {position_, 1.0F}; }
};
