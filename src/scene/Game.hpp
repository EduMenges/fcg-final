#pragma once

#include "Scene.hpp"

namespace scene {
class Game : public Scene {
   public:
    Game();

    Scene* Update(double delta) override;

    void CheckDeliverBurger();

    bool has_been_sent = false;

    HeldObject        held_object_{camera_, &entities_};
    IngredientManager manager_{&entities_, &held_object_};
    recipe::Order     order_{recipe::Recipe{}};
};
}
