#include "Camera.hpp"

#include "matrices.hpp"

glm::vec4 LookAtCamera::GetViewVec() const {
    glm::vec4 center = GetCenter();

    glm::vec4 look_at_point = glm::vec4(look_at_, 1.0F);

    return look_at_point - center;
}

glm::vec4 LookAtCamera::GetCenter() const {
    auto [theta, phi] = rotation_;

    auto r = distance_;
    auto x = r * std::cos(phi) * std::sin(theta);
    auto y = r * -std::sin(phi);
    auto z = r * std::cos(phi) * std::cos(theta);

    return {glm::vec3(x, y, z) + look_at_, 1.0F};
}

glm::vec4 FreeCamera::GetViewVec() const {
    auto [theta, phi] = rotation_;

    return {std::cos(phi) * std::sin(theta),  //
            -std::sin(phi),                   //
            std::cos(phi) * std::cos(theta),  //
            0.0F};
}

glm::mat4 Camera::GetViewMatrix() const {
    glm::vec4 center = GetCenter();

    glm::vec4 view = GetViewVec();

    return MatrixCameraView(center, view, kUp);
}

void Camera::SetRotation(glm::dvec2 rotation) {
    static constexpr double kMaxPhi = (std::numbers::pi / 2) - std::numeric_limits<double>::epsilon();
    static constexpr double kMinPhi = -kMaxPhi;

    auto [theta, phi] = rotation;

    rotation_ = {theta, std::clamp(phi, kMinPhi, kMaxPhi)};
}

void Camera::ComputeRotation(glm::dvec2 mouse_delta) {
    auto [theta, phi] = rotation_;

    glm::dvec2 new_rotation{theta - mouse_delta.x, phi + mouse_delta.y};
    SetRotation(new_rotation);
}
