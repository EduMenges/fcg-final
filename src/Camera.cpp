#include "Camera.hpp"

#include "matrices.hpp"

glm::vec4 LookAtCamera::GetViewVec() {
    glm::vec4 center = GetCenter();

    glm::vec4 look_at_point = glm::vec4(look_at_, 1.0F);

    return look_at_point - center;
}

glm::vec4 LookAtCamera::GetCenter() {
    auto [rot_x, rot_y] = rotation_;

    auto r = distance_;
    auto y = r * std::sin(rot_y);
    auto z = r * std::cos(rot_y) * std::cos(rot_x);
    auto x = r * std::cos(rot_y) * std::sin(rot_x);

    return {glm::vec3(x, y, z) + look_at_, 1.0F};
}

glm::vec4 FreeCamera::GetViewVec() {
    auto [rot_x, rot_y] = rotation_;
    return {std::cos(rot_y) * std::sin(rot_x), -std::sin(rot_y), std::cos(rot_y) * std::cos(rot_x), 0.0F};
}

glm::mat4 Camera::GetMatrix() {
    glm::vec4 center = GetCenter();

    glm::vec4 view = GetViewVec();

    return MatrixCameraView(center, view, kUp);
}

void Camera::SetRotation(Camera::Rotation rotation) {
    static constexpr double kMaxY = (std::numbers::pi / 2) - std::numeric_limits<double>::epsilon();
    static constexpr double kMinY = -kMaxY;
    rotation_ = {std::get<0>(rotation), std::clamp(std::get<1>(rotation), kMinY, kMaxY)};
}
