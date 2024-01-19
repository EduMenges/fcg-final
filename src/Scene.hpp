#pragma once

#include <list>
#include <memory>

#include "Model.hpp"
#include "Entity.hpp"

class Scene {
   public:
    using ModelContainer = std::list<std::unique_ptr<Model>>;
    using EntityContainer = std::list<std::unique_ptr<Entity>>;

    Scene(ModelContainer&& models, EntityContainer&& entities);

    virtual ~Scene() = default;

    virtual Scene* Update(float delta) {
        for (auto& entity : entities_) {
            entity->Update(delta);
        }
        return this;
    }

    virtual void Draw();

    Camera* camera_{nullptr};

   protected:
    ModelContainer  models_;
    EntityContainer entities_;
};
