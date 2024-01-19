#pragma once

#include <list>
#include <memory>
#include <variant>

#include "Model.hpp"
#include "Entity.hpp"

class Scene {
   public:
    using ModelContainer  = std::list<std::unique_ptr<Model>>;
    using EntityContainer = std::list<std::unique_ptr<Entity>>;

    Scene(ModelContainer&& models, EntityContainer&& entities);

    virtual ~Scene() = default;

    virtual Scene* Update(float delta);

    virtual void Draw();

    std::unique_ptr<Camera> camera_;

   protected:
    ModelContainer  models_;
    EntityContainer entities_;
};
