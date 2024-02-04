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
    : models_(std::move(models)), entities_(std::move(entities)), camera_(player_.GetCamera()), input_(Input::Instance()) {}

Scene* Scene::Update(double delta) {
    for (auto& entity : entities_) {
        entity->Update(delta);
    }

    player_.Update(delta);
    held_object_.Update(delta);
    manager_.Update(delta);

    CheckDeliverBurger();

    return this;
}

void Scene::CheckDeliverBurger() {
    if(input_.IsOn(GLFW_KEY_ENTER) && !has_been_sent) {
        std::cout<<"gay"<<std::endl;
        has_been_sent = true;
        held_object_.ResetBurger();
    }

    else {
        has_been_sent = input_.IsOn(GLFW_KEY_ENTER);
    }
}
