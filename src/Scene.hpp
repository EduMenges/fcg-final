#pragma once

#include <list>

#include "Model.hpp"

class Scene {
   public:
    Scene() = default;

    virtual ~Scene() {
        for (auto* e : this->models) {
            delete e;
        }
    }

    virtual Scene* Update(float dt) {
        for (auto* e : models) {
                e->Update(dt);
        }
        return this;
    }

    virtual void Draw() {
        for (auto* e : models) {
                e->Draw(*camera_);
        }
    }

    template<typename T>
    T* AddModel(T* e) {
        this->models.push_back(e);
        return e;
    }

    void RemoveModel(auto* e) {
        this->models.remove(e);
        delete e;
    }

    Camera* camera_{nullptr};

   protected:
    std::list<Model*> models;
};