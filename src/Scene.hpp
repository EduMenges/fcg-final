#pragma once

#include <list>

#include "Entity.hpp"

class Scene {
   public:
    Scene() = default;

    virtual ~Scene() {
        for (Entity* e : this->entities) {
            delete e;
        }
    }

    virtual Scene* Update(float dt) {
        for (auto* e : entities) {
                e->Update(dt);
        }
        return this;
    }

    virtual void Draw() {
        for (auto* e : entities) {
                e->Draw(*camera_);
        }
    }

    template<typename T>
    T* AddEntity(T* e) {
        this->entities.push_back(e);
        return e;
    }

    void RemoveEntity(Entity* e) {
        this->entities.remove(e);
        delete e;
    }

    Camera* camera_{nullptr};

   protected:
    std::list<Entity*> entities;
};