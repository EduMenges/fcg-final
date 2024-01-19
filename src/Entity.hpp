#pragma once

#include "Camera.hpp"
#include "model/Obj.hpp"

class Entity {
   public:
    explicit Entity(model::Obj&& model) : model_(std::move(model)) {}

    virtual ~Entity() = default;

    virtual void Update(float delta) {}

    virtual void Draw(Camera& c) {}

   protected:
    model::Obj model_;
};
