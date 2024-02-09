#pragma once

#include "Scene.hpp"

namespace scene {
class Game : public Scene {
   public:
    using ScreenContainer = std::list<std::unique_ptr<model::Screen>>;

    enum class CameraState : int8_t {
        kLookAt = -1,
        kPlayer,
    };

    Game();

    Scene* Update(double delta) override;

    void CheckDeliverBurger();

    void UpdateLookAt();

    bool              has_been_sent = false;
    ScreenContainer   screens_;
    HeldObject        held_object_{camera_, &entities_};
    IngredientManager manager_{&entities_, &held_object_};
    recipe::Order     order_{recipe::Recipe{}};
    model::Screen*    active_recipe_{nullptr};
    CameraState       camera_state_{CameraState::kPlayer};
    LookAtCamera      look_at_camera_{glm::vec3(0.0)};
};
}
