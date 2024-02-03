#pragma once

#include <list>
#include <memory>
#include <variant>

#include "Model.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "HeldObject.hpp"

class Scene {
   public:
    using ModelContainer  = std::list<std::unique_ptr<Model>>;
    using EntityContainer = std::list<std::unique_ptr<Entity>>;

    Scene(Scene::ModelContainer&& models, Scene::EntityContainer&& entities);

    Scene(Scene&& other) = default;

    virtual ~Scene() = default;

    virtual Scene* Update(double delta);

    virtual void Draw();

    Player player_;
   protected:
    ModelContainer  models_;
    EntityContainer entities_;

    Camera* camera_{nullptr};
    HeldObject held_object_{camera_};
};
