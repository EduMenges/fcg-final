#pragma once

#include "trait/Updatable.hpp"
#include "Camera.hpp"
#include "model/Obj.hpp"

class Entity: public trait::Updatable {
   public:
    explicit Entity(model::Obj&& model) : model_(std::move(model)) {}

    ~Entity() override = default;

    virtual void Draw(Camera& c) { model_.Draw(c); }

   protected:
    model::Obj model_;
};
