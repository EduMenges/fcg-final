#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "matrices.hpp"

class Camera {
   public:
    using Rotation = std::tuple<double, double>;

    Camera()          = default;
    virtual ~Camera() = default;

    virtual glm::mat4 GetMatrix();

    virtual glm::vec4 GetViewVec() = 0;

    void SetRotation(Rotation rotation);

   protected:
    static constexpr glm::vec4 kUp{0.0F, 1.0F, 0.0F, 0.0F};

    virtual glm::vec4 GetCenter() = 0;
    Rotation          rotation_{0.0, 0.0};
};

class LookAtCamera : public Camera {
   public:
    explicit LookAtCamera(glm::vec3 look_at) : look_at_(look_at) {}

    glm::vec4 GetViewVec() override;

   private:
    glm::vec4 GetCenter() override;

    glm::vec3 look_at_;
    double    distance_ = 3.5;
};

class FreeCamera : public Camera {
   public:
    glm::vec4 GetViewVec() override;

    [[nodiscard]] constexpr glm::vec3 GetPosition() const { return position_; }

    constexpr void SetPosition(glm::vec3 position) { position_ = position; }

   private:
    glm::vec4 GetCenter() override { return {position_, 1.0F}; }

    glm::vec3 position_ = glm::vec3(0);
};
