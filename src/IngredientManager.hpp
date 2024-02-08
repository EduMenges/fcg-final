#pragma once

#include "entity/ingredient/Ingredient.hpp"
#include "entity/ingredient/IngredientImports.hpp"
#include "HeldObject.hpp"
#include "input/Keys.hpp"
#include "input/Mouse.hpp"
#include "singleton/Input.hpp"

class IngredientManager {
   public:
    static constexpr float kY = 0.0f;
    static constexpr size_t kIngredientAmount = 10;

    using EntityContainer = std::list<std::unique_ptr<Entity>>;

    explicit IngredientManager(EntityContainer* ec, HeldObject* ho);

    void Init();

    void Update(double delta);

    EntityContainer* entities_;
    HeldObject*      held_object_;

    ingredient::Lettuce*       lettuce_ref;
    ingredient::Egg*           egg_ref;
    ingredient::Tomato*        tomato_ref;
    ingredient::Cheese*        cheese_ref;
    ingredient::Bacon*         bacon_ref;
    ingredient::BeefPatty*     beef_ref;
    ingredient::TopBun*        bun_ref;
    ingredient::KetchupBottle* ketchup_ref;
    ingredient::MustardBottle* mustard_ref;

    float table_y;
};
