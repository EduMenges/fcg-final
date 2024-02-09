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
#include "entity/Screen.hpp"

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

    Input& input_;

};
