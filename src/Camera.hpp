#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "matrices.hpp"

class Camera {
   public:
    Camera()          = default;
    virtual ~Camera() = default;

    [[nodiscard]] glm::vec4 GetCameraPosition() const {
        return GetCenter();
    }

    [[nodiscard]] virtual glm::mat4 GetViewMatrix() const;

    [[nodiscard]] virtual glm::vec4 GetViewVec() const = 0;

    void SetRotation(glm::dvec2 rotation);

    void ComputeRotation(glm::dvec2 mouse_delta);

    static constexpr glm::vec4 kUp{0.0F, 1.0F, 0.0F, 0.0F};
   protected:

    [[nodiscard]] virtual glm::vec4 GetCenter() const = 0;
    glm::dvec2          rotation_{0.0, 0.0};
};

class LookAtCamera : public Camera {
   public:
    explicit LookAtCamera(glm::vec3 look_at) : look_at_(look_at) {}

    [[nodiscard]] glm::vec4 GetViewVec() const override;

   private:
    [[nodiscard]] glm::vec4 GetCenter() const override;

    glm::vec3 look_at_;
    double    distance_ = 3.5;
};

class FreeCamera : public Camera {
   public:
    FreeCamera() = default;

    explicit FreeCamera(glm::vec4 position): position_(position) {}

    [[nodiscard]] glm::vec4 GetViewVec() const override;

    [[nodiscard]] constexpr glm::vec4 GetPosition() const { return position_; }

    constexpr void SetPosition(glm::vec4 position) { position_ = position; }

   private:
    [[nodiscard]] glm::vec4 GetCenter() const override { return GetPosition() + glm::vec4(0.0F, 1.2F, 0.0F, 0.0F); }

    glm::vec4 position_{0, 0, 0, 1};
};
