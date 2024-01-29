#pragma once

#include "Camera.hpp"
#include "Obj.hpp"

class Model {
   public:
    explicit Model(glm::vec3 position, glm::vec3 scale = glm::vec3(1), glm::vec3 rotation = glm::vec3(0))
        : position_(position), scale_(scale), rotation_(rotation) {}

    Model(Model&& other) = default;

    Model(const Model& other) = delete;

    virtual ~Model() = default;

    virtual void Draw(Camera& c);

    virtual Obj& GetObj() = 0;

    glm::vec3 position_{0};
    glm::vec3 scale_{1};
    glm::vec3 rotation_{0};
};
