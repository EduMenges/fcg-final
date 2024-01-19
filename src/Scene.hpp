#pragma once

#include <list>
#include <memory>
#include <variant>

#include "Model.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class Scene {
   public:
    using ModelContainer  = std::list<std::unique_ptr<Model>>;
    using EntityContainer = std::list<std::unique_ptr<Entity>>;

    Scene(Scene::ModelContainer&& models, Scene::EntityContainer&& entities);

    virtual ~Scene() = default;

    virtual Scene* Update(double delta);

    virtual void Draw();

   protected:
    ModelContainer  models_;
    EntityContainer entities_;

    Player player_;
    Camera* camera_{nullptr};
};
