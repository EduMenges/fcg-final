#pragma once
#include "Entity.hpp"
#include "entity/ingredient/BottomBun.hpp"
#include "singleton/Input.hpp"
#include "input/Mouse.hpp"
#include "entity/ingredient/IngredientImports.hpp"

class HeldObject {
   public:
    explicit HeldObject(Camera* c);

    Entity* object;
    glm::vec3 old_position, old_rotation;
    bool switch_up = false;

    void Set(Entity& new_object);
    void Unset();

    void Update(double delta);
    Camera* camera;

    void SwitchHeld();



};

