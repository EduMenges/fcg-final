#pragma once

#include <list>
#include <memory>
#include <variant>
#include <iostream>

#include "Model.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "HeldObject.hpp"
#include "IngredientManager.hpp"
#include "recipe/Order.hpp"
#include "singleton/Input.hpp"
#include "input/Keys.hpp"

class Scene {
   public:
    using ModelContainer  = std::list<std::unique_ptr<Model>>;
    using EntityContainer = std::list<std::unique_ptr<Entity>>;

    Scene(Scene::ModelContainer&& models, Scene::EntityContainer&& entities);

    Scene(Scene&& other) = default;

    virtual ~Scene() = default;

    virtual Scene* Update(double delta);

    virtual void Draw();

    Player player_;
   protected:
    ModelContainer  models_;
    EntityContainer entities_;

    Camera* camera_{nullptr};
    HeldObject held_object_{camera_, &entities_};
    IngredientManager manager_{&entities_, &held_object_};
    recipe::Order order_{recipe::Recipe{}};

    Input& input_;

    void CheckDeliverBurger();
    bool has_been_sent = false;
};
