#include "Menu.hpp"
#include "entity/Burger.hpp"
#include "Player.hpp"

scene::Menu::Menu() : Scene({}, {}) {
    entities_.emplace_back(std::make_unique<entity::Burger>(glm::vec3{1, 1, 3}));
    player_.SetPosition({3.0F, 2.0F, 3.5F, 1.0F});
    camera_->SetRotation({-2.45, 0.45});
}
