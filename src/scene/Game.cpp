#include "Game.hpp"
#include "entity/Burger.hpp"
#include "model/Table.hpp"

#include "entity/ingredient/IngredientImports.hpp"
#include "Player.hpp"
#include "singleton/Input.hpp"
#include "model/Floor.hpp"
#include "model/Wall.hpp"
#include "model/Oven.hpp"
#include "model/Generic.hpp"
#include <iostream>
#include <numbers>
#include "model/Screen.hpp"
#include "singleton/Window.hpp"
#include "entity/UFO.hpp"

scene::Game::Game() : Scene({}, {}) {
    auto& table      = models_.emplace_back(std::make_unique<model::Table>(glm::vec3{0.0F, 0.0F, -2.0F}));
    float table_y    = table->GetBoundingBox().max_.y;
    manager_.table_y = table_y;

    glm::vec3 burger_pos                   = table->position_;
    burger_pos.y                           = table_y;
    std::unique_ptr<entity::Burger> burger = std::make_unique<entity::Burger>(burger_pos);

    held_object_.LinkBurger(*burger);
    entities_.emplace_back(std::make_unique<entity::UFO>(*burger));
    entities_.emplace_back(std::move(burger));

    // Demais mesas

    models_.emplace_back(std::make_unique<model::Table>(glm::vec3{1.2F, 0.0F, -2.0F}));
    models_.emplace_back(std::make_unique<model::Table>(glm::vec3{-1.2F, 0.0F, -2.0F}));
    models_.emplace_back(std::make_unique<model::Table>(glm::vec3{1.2F, 0.0F, 2.0F}));
    models_.emplace_back(std::make_unique<model::Table>(glm::vec3{-1.2F, 0.0F, 2.0F}));
    models_.emplace_back(std::make_unique<model::Table>(glm::vec3{0.0F, 0.0F, 2.0F}));

    models_.emplace_back(std::make_unique<model::Table>(glm::vec3{2.0F, 0.0F, 0.7F}))->rotation_.y =
        glm::radians(90.0F);
    models_.emplace_back(std::make_unique<model::Table>(glm::vec3{2.0F, 0.0F, -0.7F}))->rotation_.y =
        glm::radians(90.0F);
    models_.emplace_back(std::make_unique<model::Table>(glm::vec3{-2.0F, 0.0F, 0.7F}))->rotation_.y =
        glm::radians(90.0F);
    models_.emplace_back(std::make_unique<model::Table>(glm::vec3{-2.0F, 0.0F, -0.7F}))->rotation_.y =
        glm::radians(90.0F);

    models_.emplace_back(std::make_unique<model::Floor>());
    models_.emplace_back(
        std::make_unique<model::Floor>(glm::vec3{0.0F, 4.0F, 0.0F}, glm::vec3{0.0F, 0.0F, glm::radians(180.0F)}));

    // Coloca as paredes no lugar

    constexpr size_t    kAmountOfWalls = 4;
    constexpr float     kWallSize      = 3.0F;
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

    models_.emplace_back(std::make_unique<model::Oven>(glm::vec3(3.4F, 0.0, -5.5F)));

    models_.emplace_back(std::make_unique<model::Generic>(
        "../../../data/fridge/Fridge.obj", glm::vec3{-3.5F, 0.0F, -6.0F}, glm::vec3(0.011F), glm::vec3(0.0F)));

    player_.SetPosition({0.0F, 0.0, kWallSize * 1.5, 1.0F});
    camera_->SetRotation({4 * M_PI_4f, 0.0});

    constexpr float kScreenY = 0.5F;
    constexpr float kScreenZ = -kWallSize * 3;
    screens_.emplace_back(std::make_unique<model::Screen>(glm::vec3(0, kScreenY, kScreenZ), recipe::RecipeName::BLT));
    screens_.emplace_back(std::make_unique<model::Screen>(glm::vec3(0, kScreenY, kScreenZ), recipe::RecipeName::SALAD));
    screens_.emplace_back(
        std::make_unique<model::Screen>(glm::vec3(0, kScreenY, kScreenZ), recipe::RecipeName::CHEESEBURGER));
    screens_.emplace_back(
        std::make_unique<model::Screen>(glm::vec3(0, kScreenY, kScreenZ), recipe::RecipeName::MEATLOVER));
    screens_.emplace_back(
        std::make_unique<model::Screen>(glm::vec3(0, kScreenY, kScreenZ), recipe::RecipeName::SPECIAL));

    for (auto& screen : screens_) {
        if (screen->recipe == order_.recipe_ref.name) {
            screen->position_.z = -5.8F;
            screen->rotation_.y = -glm::radians(90.0F);
            screen->scale_      = glm::vec3(0.9);
            active_recipe_      = screen.get();
        }
    }

    manager_.Init();
}

Scene* scene::Game::Update(double delta) {
    Scene::Update(delta);

    for (auto& screen : screens_) {
        screen->Draw(*camera_);
    }

    // We need to use this instead of the input singleton due to its latency.

    static bool was_on;
    static bool is_on;

    was_on = is_on;
    is_on  = glfwGetKey(Window::Instance().GetWindow(), GLFW_KEY_L) == GLFW_PRESS;

    if (camera_state_ == CameraState::kLookAt) {
        UpdateLookAt();
    }

    if (is_on && !was_on) {
        switch (camera_state_) {
            case CameraState::kLookAt:
                camera_state_   = CameraState::kPlayer;
                camera_         = player_.GetCamera();
                player_.paused_ = false;
                break;
            case CameraState::kPlayer:
                camera_state_ = CameraState::kLookAt;
                camera_       = &look_at_camera_;
                look_at_camera_.SetLookAt(active_recipe_->position_ + glm::vec3(0.0, 1.0F, 0.0));
                look_at_camera_.SetRotation({0.0F, 0.0F});
                player_.paused_ = true;
                break;
        }
    }

    held_object_.Update(delta);
    manager_.Update(delta);

    CheckDeliverBurger();

    return this;
}

void scene::Game::CheckDeliverBurger() {
    if (input_.IsOn(GLFW_KEY_ENTER) && !has_been_sent) {
        has_been_sent = true;
        int score     = order_.Score(held_object_.burger);
        if (!held_object_.burger->is_correct_) {
            held_object_.ResetBurger();
        }
    } else {
        has_been_sent = input_.IsOn(GLFW_KEY_ENTER);
    }
}

void scene::Game::UpdateLookAt() {
    auto [dx, dy] = Input::Instance().GetDelta() * 0.01;
    look_at_camera_.ComputeRotation({dx, dy});
}
