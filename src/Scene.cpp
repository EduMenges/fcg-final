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
    : models_(std::move(models)), entities_(std::move(entities)) {}

Scene* Scene::Update(float delta) {
    for (auto& entity : entities_) {
        entity->Update(delta);
    }
    return this;
}
