#pragma once

#include "glm/glm.hpp"
#include "input/Keys.hpp"
#include "coords/Spheric.hpp"
#include "matrices.hpp"
#include <numbers>
#include <algorithm>

class Camera {
   public:
    Camera() = default;

    constexpr void SetPosition(glm::vec4 coords) noexcept { position_ = coords; }

    virtual glm::mat4 GetViewMatrix() = 0;

    virtual void Update(float delta_t) {
        float const     cameraSpeed = 2.0F;

        glm::vec4 const w           = -(Normalize(view_));
        glm::vec4 const u           = Normalize(CrossProduct(kUpVector, w));

        if (*keys_.IsOn('W')) {
            position_ -= w * cameraSpeed * delta_t;
        }
        if (*keys_.IsOn('S')) {
            position_ += w * cameraSpeed * delta_t;
        }
        if (*keys_.IsOn('A')) {
            position_ -= u * cameraSpeed * delta_t;
        }
        if (*keys_.IsOn('D')) {
            position_ += u * cameraSpeed * delta_t;
        }

        position_.y = 0.8F;
    }

   protected:
    static constexpr glm::vec4 kUpVector = {0.0f, 1.0f, 0.0f, 0.0f};

    /// Where the camera is located, in cartesian coordinates.
    glm::vec4 position_ = {0.4F, 0.8F, 0.0F, 1.0F};

    coords::Spheric s_position_;

    float nearPlane_ = -0.1F;
    float farPlane_  = -100.0F;

    /// Orientation as to where the camera is pointing to.
    glm::vec4 view_;

    /// Keyboard control variables.
    input::Keys keys_;
};

class FreeCamera : public Camera {
   public:
    FreeCamera() = default;

    void UpdateSpheric(float angle) { this->s_position_.theta -= angle; }

    void UpdateViewVector(float angle_x, float angle_y) {
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

    glm::mat4 GetViewMatrix() override { return MatrixCameraView(position_, view_, kUpVector); }
};

class LookAtCamera : public Camera {
   public:
    void UpdateSpheric(float dx, float dy) {
        // Angle should be in [0, 45] degreess to avoid player looking inside the ground.
        float const kNewPhi = std::clamp(this->s_position_.phi + 0.003F * dy, 0.0F, std::numbers::pi_v<float> / 4);

        // Atualiza as coordendas esféricas
        this->s_position_.phi = kNewPhi;
        this->s_position_.theta -= 0.003F * dx;
    }

    glm::mat4 GetViewMatrix() override {
        const glm::vec4 pos(s_position_.radius * cos(s_position_.phi) * sin(s_position_.theta),
                            s_position_.radius * sin(s_position_.phi),
                            s_position_.radius * cos(s_position_.phi) * cos(s_position_.theta),  //
                            1.0F);

        glm::vec4 position = look_at_ + pos;
        position.w         = 1.0F;

        return MatrixCameraView(position, view_, Camera::kUpVector);
    }

    [[nodiscard]] constexpr glm::vec4 GetLookAt() const noexcept { return look_at_; }

    void SetLookAt(glm::vec4 look_at) { look_at_ = look_at; }

    void UpdateViewVector() {
        // Calcula a posição cartesiana a partir da posição esférica
        glm::vec4 vec = look_at_;

        vec.x += s_position_.radius * cos(s_position_.phi) * sin(s_position_.theta);
        vec.y += s_position_.radius * sin(s_position_.phi);
        vec.z += s_position_.radius * cos(s_position_.phi) * cos(s_position_.theta);
        vec.w = 1.0f;

        view_ = Normalize(GetLookAt() - vec);
    }

    void Update(float delta_t) override {
        Camera::Update(delta_t);
        UpdateViewVector();
    }

   private:
    glm::vec4 look_at_ = {0.5F, 0.8F, 0.0F, 1.0F};
};
