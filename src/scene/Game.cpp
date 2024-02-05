#include "Game.hpp"
#include "entity/Burger.hpp"
#include "entity/Table.hpp"
#include "entity/KetchupBottle.hpp"

#include "entity/MustardBottle.hpp"
#include "entity/ingredient/IngredientImports.hpp"
#include "Player.hpp"
#include "singleton/Input.hpp"
#include "model/Floor.hpp"
#include "model/Wall.hpp"
#include "model/Oven.hpp"
#include "model/Generic.hpp"
#include <iostream>
#include <numbers>

scene::Game::Game() : Scene({}, {}) {
    auto& table   = *entities_.emplace_back(std::make_unique<entity::Table>(glm::vec3{0.0F, 0.0F, 0.0F}));
    float table_y = table.GetBoundingBox().max_.y;

    glm::vec3 burger_pos                   = table.position_;
    burger_pos.y                           = table_y;
    std::unique_ptr<entity::Burger> burger = std::make_unique<entity::Burger>(burger_pos);

    held_object_.LinkBurger(*burger);
    entities_.emplace_back(std::move(burger));

    models_.emplace_back(std::make_unique<model::Floor>());

    constexpr size_t    kAmountOfWalls = 3;
    constexpr float     kWallSize      = 3.0f;
    constexpr glm::vec3 kCenterDisplacement{-(kWallSize * kAmountOfWalls) / 2, 0.0, (kWallSize * kAmountOfWalls) / 2};

    for (size_t i = 0; i < kAmountOfWalls; ++i) {
        auto fi = static_cast<float>(i);

        models_.emplace_back(std::make_unique<model::Wall>(glm::vec3(kWallSize * fi, 0.0F, 0.0F) + kCenterDisplacement,
                                                           glm::vec3(1.0), glm::vec3(0.0, 0.0, 0.0)));

        models_.emplace_back(std::make_unique<model::Wall>(
            glm::vec3(kWallSize * kAmountOfWalls, 0.0F, -fi * kWallSize) + kCenterDisplacement, glm::vec3(1.0),
            glm::vec3(0.0, std::numbers::pi_v<float> / 2, 0.0)));

        models_.emplace_back(std::make_unique<model::Wall>(
            glm::vec3((kWallSize) * (fi + 1.0F), 0.0F, -kWallSize * kAmountOfWalls) + kCenterDisplacement,
            glm::vec3(1.0), glm::vec3(0.0, std::numbers::pi_v<float>, 0.0)));

        models_.emplace_back(
            std::make_unique<model::Wall>(glm::vec3(0.0F, 0.0F, -kWallSize * (fi + 1.0F)) + kCenterDisplacement,
                                          glm::vec3(1.0), glm::vec3(0.0, std::numbers::pi_v<float> * 3 / 2, 0.0)));
    }

    models_.emplace_back(std::make_unique<model::Oven>(glm::vec3(3.4F, 0.0, -4.1F)));

    models_.emplace_back(std::make_unique<model::Generic>("../../../data/fridge/Fridge.obj",
                                                          glm::vec3{-3.5F, 0.0F, -4.4F}, glm::vec3(0.011F)));

    player_.SetPosition({0.0F, 0.0, 3.0F, 1.0F});
    camera_->SetRotation({4 * M_PI_4f, 0.0});

    manager_.Init();
}
