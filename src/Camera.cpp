#include "Camera.hpp"

#include "matrices.hpp"

glm::vec4 LookAtCamera::GetViewVec() {
    glm::vec4 center = GetCenter();

    glm::vec4 look_at_point = glm::vec4(look_at_, 1.0F);

    return look_at_point - center;
}

glm::vec4 LookAtCamera::GetCenter() {
    float r = distance_;
    float y = r * std::sin(rot_y_);
    float z = r * std::cos(rot_y_) * std::cos(rot_x_);
    float x = r * std::cos(rot_y_) * std::sin(rot_x_);

    return {glm::vec3(x, y, z) + look_at_, 1.0F};
}

glm::vec4 FreeCamera::GetViewVec() {
    return {std::cos(rot_y_) * std::sin(rot_x_), -std::sin(rot_y_), std::cos(rot_y_) * std::cos(rot_x_), 0.0F};
}

glm::mat4 Camera::GetMatrix() {
    glm::vec4 center = GetCenter();

    glm::vec4 view = GetViewVec();

    return MatrixCameraView(center, view, kUp);
}
