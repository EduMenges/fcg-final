#include "Scene.hpp"

void Scene::Draw() {
    for (auto& model : models_) {
        model->Draw(*camera_);
    }

    for (auto& entity : entities_) {
        entity->Draw(*camera_);
    }
}

Scene::Scene(Scene::ModelContainer&& models, Scene::EntityContainer&& entities)
    : models_(std::move(models)), entities_(std::move(entities)), camera_(player_.GetCamera()) {}

Scene* Scene::Update(double delta) {
    for (auto& entity : entities_) {
        entity->Update(delta);
    }

    player_.Update(delta);

    return this;
}
