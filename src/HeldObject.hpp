#pragma once

#include "Entity.hpp"
#include "entity/ingredient/BottomBun.hpp"
#include "singleton/Input.hpp"
#include "input/Mouse.hpp"
#include "entity/ingredient/IngredientImports.hpp"
#include "entity/Burger.hpp"
#include <list>

class HeldObject {
   public:
    using EntityContainer = std::list<std::unique_ptr<Entity>>;

    explicit HeldObject(Camera* c, EntityContainer* ec);

    void Set(ingredient::Ingredient& new_object);
    void Unset();
    void LinkBurger(entity::Burger& b);

    void Update(double delta);

    void ToBurger();

    void ResetBurger();

    ingredient::Ingredient* object_{nullptr};
    glm::vec3               old_position_{};
    glm::vec3               old_rotation_{};

    Camera*          camera;
    entity::Burger*  burger{nullptr};
    EntityContainer* entities;
};
