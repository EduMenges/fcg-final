#pragma once
#include "Entity.hpp"
#include "entity/ingredient/BottomBun.hpp"
#include "singleton/Input.hpp"
#include "input/Mouse.hpp"
#include "entity/ingredient/IngredientImports.hpp"
#include "entity/Burger.hpp"

class HeldObject {
   public:
    explicit HeldObject(Camera* c);

    ingredient::Ingredient* object;
    glm::vec3 old_position, old_rotation;
    bool switch_up = false;

    void Set(ingredient::Ingredient& new_object);
    void Unset();
    void LinkBurger(entity::Burger& b);

    void Update(double delta);
    Camera* camera;
    entity::Burger* burger;

    void SwitchHeld();

};

