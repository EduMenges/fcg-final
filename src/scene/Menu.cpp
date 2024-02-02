#include "Menu.hpp"
#include "entity/Burger.hpp"
#include "entity/Table.hpp"
#include "entity/KetchupBottle.hpp"

#include "entity/MustardBottle.hpp"
#include "entity/ingredient/Mustard.hpp"
#include "entity/ingredient/Egg.hpp"
#include "entity/ingredient/Ketchup.hpp"
#include "entity/ingredient/Cheese.hpp"
#include "Player.hpp"
#include "singleton/Input.hpp"

scene::Menu::Menu() : Scene({}, {}) {
    entities_.emplace_back(std::make_unique<entity::Table>(glm::vec3{3, .8, 2}));
    entities_.emplace_back(std::make_unique<entity::MustardBottle>(glm::vec3{3, 1.7, 2}));
    entities_.emplace_back(std::make_unique<ingredient::Cheese>(glm::vec3{4, 1.7, 2}));

    player_.SetPosition({3.0F, 2.0F, 3.5F, 1.0F});
    camera_->SetRotation({-2.45, 0.45});
}
