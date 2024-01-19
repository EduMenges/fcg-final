#include "Player.hpp"
#include "singleton/Input.hpp"

void Player::Update(double delta) {
    auto [dx, dy] = Input::Instance().GetDelta();

    camera_.SetRotation({dx * kMouseAcceleration, dy * kMouseAcceleration});

    glm::vec4 w = camera_.GetViewVec();
    w.y         = 0.0;

    glm::vec4 u = CrossProduct(glm::vec4(0, 1, 0, 0), w);

    w = w / Norm(w);
    u = u / Norm(u);

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

    if (Norm(movement) > 0) {
        movement = movement / Norm(movement);
    }

    glm::vec3 new_pos =
        GetPosition() + glm::vec3(movement.x, movement.y, movement.z) * static_cast<float>(delta * kMoveSpeed);

    camera_.SetPosition(new_pos);
}
