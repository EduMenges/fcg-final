#pragma once
#include "Entity.hpp"
#include "singleton/Input.hpp"
#include "input/Mouse.hpp"

class HeldObject {
   public:
    explicit HeldObject(Camera* c);

    Entity* object;
    glm::vec3 old_position, old_rotation;

    void Set(Entity& new_object);
    void Update(double delta);
    Camera* camera;

};

