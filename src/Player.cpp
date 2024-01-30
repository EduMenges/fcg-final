#include "Player.hpp"
#include "singleton/Input.hpp"
#include "singleton/Collision.hpp"

void Player::Update(double delta) {
    camera_.ComputeRotation(Input::Instance().GetDelta() * kMouseAcceleration);

    // Camera target
    glm::vec4 w = camera_.GetViewVec();

    // Camera-facing horizontal movement
    glm::vec4 forward = Normalize(glm::vec4(w.x, 0, w.y, 0));

    // Camera right
    glm::vec4 right = CrossProduct(Camera::kUp, forward);

    auto movement = glm::vec4(0);

    auto& input = Input::Instance();
    if (input.IsOn(GLFW_KEY_W)) {
        movement += forward;
    }
    if (input.IsOn(GLFW_KEY_S)) {
        movement -= forward;
    }
    if (input.IsOn(GLFW_KEY_A)) {
        movement += right;
    }
    if (input.IsOn(GLFW_KEY_D)) {
        movement -= right;
    }

    glm::vec3 new_pos = GetPosition() + movement * static_cast<float>(delta * kMoveSpeed);
    HitBox hb = kBaseHitBox + new_pos;

    if (!Collision::Instance().ColidesWithBox(hb)) {
        camera_.SetPosition(glm::vec4(new_pos, 1.0F));
    }
}
