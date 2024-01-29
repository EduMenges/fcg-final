#include "Player.hpp"
#include "singleton/Input.hpp"
#include "singleton/Collision.hpp"

void Player::Update(double delta) {
    camera_.ComputeRotation(Input::Instance().GetDelta() * kMouseAcceleration);

    // Camera target
    glm::vec4 w = camera_.GetViewVec();

    // Camera right
    glm::vec4 u = CrossProduct(Camera::kUp, w);

    auto movement = glm::vec4(0);

    auto& input = Input::Instance();
    if (input.IsOn(GLFW_KEY_W)) {
        movement += w;
    }
    if (input.IsOn(GLFW_KEY_S)) {
        movement -= w;
    }
    if (input.IsOn(GLFW_KEY_A)) {
        movement += u;
    }
    if (input.IsOn(GLFW_KEY_D)) {
        movement -= u;
    }

    glm::vec3 new_pos = GetPosition() + movement * static_cast<float>(delta * kMoveSpeed);
    HitBox hb = kBaseHitBox + new_pos;

    if (!Collision::Instance().ColidesWithBox(hb)) {
        camera_.SetPosition(glm::vec4(new_pos, 1.0F));
    }
}
