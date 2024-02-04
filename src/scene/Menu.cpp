#include "Menu.hpp"
#include "entity/Burger.hpp"
#include "entity/Table.hpp"
#include "entity/KetchupBottle.hpp"

#include "entity/MustardBottle.hpp"
#include "entity/ingredient/IngredientImports.hpp"
#include "Player.hpp"
#include "singleton/Input.hpp"
#include "model/Floor.hpp"
#include <iostream>

scene::Menu::Menu() : Scene({}, {}) {
    auto& table   = *entities_.emplace_back(std::make_unique<entity::Table>(glm::vec3{0.0F, 0.0F, 0.0F}));
    float table_y = table.GetBoundingBox().max_.y;

    glm::vec3 burger_pos = table.position_;
    burger_pos.y         = table_y;
    std::unique_ptr<entity::Burger> burger = std::make_unique<entity::Burger>(burger_pos);
    held_object_.LinkBurger(*burger);
    entities_.emplace_back(std::move(burger));
    // entities_.emplace_back(std::make_unique<ingredient::BeefPatty>(glm::vec3{4, 1.7, 2}));

    /* std::unique_ptr<ingredient::Ingredient> ing = std::make_unique<ingredient::Lettuce>(glm::vec3{4, 1.7, 2});
    held_object_.Set(*ing);
    entities_.emplace_back(std::move(ing)); */

    models_.emplace_back(std::make_unique<model::Floor>());

    player_.SetPosition({3.0F, 0.0, 3.5F, 1.0F});
    camera_->SetRotation({-2.45, 0.45});
    manager_.Init();
}
