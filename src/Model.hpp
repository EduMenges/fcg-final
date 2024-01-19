#pragma once

#include "Camera.hpp"

class Model {
   public:
    Model() = default;

    explicit Model(glm::vec3 position = glm::vec3(0), glm::vec3 scale = glm::vec3(0)): position_(position), scale_(scale) {}

    virtual ~Model() = default;

    virtual void Draw(Camera& c) {}

    glm::vec3 position_{0};
    glm::vec3 scale_{1};
    glm::vec3 rotation_{0};
};
