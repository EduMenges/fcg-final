#pragma once

#include "trait/Updatable.hpp"
#include "Camera.hpp"

class Player : public trait::Updatable {
   public:
    Player() = default;

    Player(glm::vec4 position) : camera_(position){}

    void Update(double delta) override;

    FreeCamera* GetCamera() {
        return &camera_;
    }

    void SetPosition(glm::vec4 position) {
        camera_.SetPosition(position);
    }

   private:
    static constexpr double kMouseAcceleration = 0.01;
    static constexpr double kMoveSpeed = 5.0;

    [[nodiscard]] constexpr glm::vec4 GetPosition() const { return camera_.GetPosition();}

    FreeCamera camera_;

};
