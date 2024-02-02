#pragma once

#include "trait/Updatable.hpp"
#include "Camera.hpp"
#include "singleton/Collision.hpp"

class Player : public trait::Updatable {
   public:
    Player() = default;

    Player(glm::vec4 position) : camera_(position) {}

    void Update(double delta) override;

    FreeCamera* GetCamera() { return &camera_; }

    void SetPosition(glm::vec4 position) { camera_.SetPosition(position); }

   private:
    static constexpr HitBox kBaseHitBox{glm::vec3(-0.5, 0, -0.5F), glm::vec3(0.5, 1.8, 0.5F)};
    static constexpr double kMouseAcceleration{0.008};
    static constexpr double kMoveSpeed{3.0};

    [[nodiscard]] constexpr glm::vec4 GetPosition() const { return camera_.GetPosition(); }

    FreeCamera camera_;
};
