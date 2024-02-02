#include "Menu.hpp"
#include "entity/Burger.hpp"
#include "entity/Table.hpp"
#include "entity/KetchupBottle.hpp"
#include "Player.hpp"
#include "singleton/Input.hpp"
#include "entity/FlyingKetchup.hpp"

scene::Menu::Menu() : Scene({}, {}) {
    entities_.emplace_back(std::make_unique<entity::Table>(glm::vec3{3, .8, 2}));
    entities_.emplace_back(std::make_unique<entity::KetchupBottle>(glm::vec3{3, 1.7, 2}));
    entities_.emplace_back(std::make_unique<entity::FlyingKetchup>());

    player_.SetPosition({3.0F, 2.0F, 3.5F, 1.0F});
    camera_->SetRotation({-2.45, 0.45});
}
