#include "Scene.hpp"

void Scene::Draw() {
    for (auto& model : models_) {
        model->Draw(*camera_);
    }

    for (auto& entity : entities_) {
        entity->Draw(*camera_);
    }
}

Scene::Scene(std::unique_ptr<Camera>&& camera, Scene::ModelContainer&& models, Scene::EntityContainer&& entities)
    : camera_(std::move(camera)), models_(std::move(models)), entities_(std::move(entities)) {}

Scene* Scene::Update(float delta) {
    for (auto& entity : entities_) {
        entity->Update(delta);
    }

    camera_->Update(delta);

    return this;
}
