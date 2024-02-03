#pragma once
#include "Entity.hpp"
#include "singleton/Input.hpp"
#include "input/Mouse.hpp"

class HeldObject {
   public:
    explicit HeldObject();

    Entity* object;

    void Set(Entity& new_object);
    void Update(double delta);


};

