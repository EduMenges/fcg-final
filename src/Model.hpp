#pragma once

#include "Camera.hpp"

class Model {
   public:
    virtual ~Model() = default;

    virtual void Draw(Camera& c) {}
};
