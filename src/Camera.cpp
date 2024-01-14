#include "Camera.hpp"

void LookAtCamera::UpdateViewVector() {
    // Calcula a posição cartesiana a partir da posição esférica
    glm::vec4 vec = look_at_;

    vec.x += s_position_.radius * std::cos(s_position_.phi) * std::sin(s_position_.theta);
    vec.y += s_position_.radius * std::sin(s_position_.phi);
    vec.z += s_position_.radius * std::cos(s_position_.phi) * std::cos(s_position_.theta);
    vec.w = 1.0F;

    view_ = Normalize(GetLookAt() - vec);
}

void FreeCamera::UpdateViewVector(float angle_x, float angle_y) {
    // Caso angulo não tenha sido alterado, retorna
    if (angle_x == 0 && angle_y == 0) {
        return;
    }

    // Trava da rotação vertical
    glm::vec4 side = CrossProduct(Camera::kUpVector, view_);

    // Calcula o lado, para rotacionar verticalmente
    glm::vec4 aux = view_ * MatrixRotate(-angle_y, side);  // Rotação no eixo lado (vertical)

    // Testa se o novo valor de lado é igual ao antigo
    if (DotProduct(side, CrossProduct(Camera::kUpVector, aux)) > 0) {
        view_ = aux;
    }

    // Atualiza vetor view
    view_ = Normalize(view_ * MatrixRotate(angle_x, kUpVector));
}
