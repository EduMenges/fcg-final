#pragma once

#include "trait/Updatable.hpp"
#include "Camera.hpp"

class Player : public trait::Updatable {
   public:
    Player() = default;

    void Update(double delta) override;

    FreeCamera* GetCamera() {
        return &camera_;
    }

   private:
    static constexpr double kMouseAcceleration = 0.01;
    static constexpr double kMoveSpeed = 5.0;

    [[nodiscard]] constexpr glm::vec3 GetPosition() const { return camera_.GetPosition();}

    FreeCamera camera_;

};
