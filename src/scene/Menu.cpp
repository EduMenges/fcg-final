#include "Menu.hpp"
#include "entity/Burger.hpp"

scene::Menu::Menu() : Scene(std::make_unique<FreeCamera>(), {}, {}) { entities_.emplace_back(std::make_unique<entity::Burger>(glm::vec3{1, 1, 3})); }
