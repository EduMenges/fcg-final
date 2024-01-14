#pragma once

#include "Camera.hpp"

class Entity {
   public:
    virtual ~Entity() = default;
    virtual void Update(float deltaTime) {}
    virtual void Draw(Camera& c) {}
};
