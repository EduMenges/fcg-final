#pragma once

#include "trait/Updatable.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "singleton/Collision.hpp"

class Entity : public trait::Updatable, public Model {
   public:
    explicit Entity(glm::vec3 position, glm::vec3 scale = glm::vec3(1), glm::vec3 rotation = glm::vec3(0))
        : Model(position, scale, rotation) {}

    Entity(Entity&& other) = default;

    ~Entity() override = default;
};
