#pragma once
#include "Recipe.hpp"
#include "entity/Burger.hpp"

namespace recipe {

class Order {
   public:
    explicit Order(Recipe recipe);

    Recipe recipe;
    int score;
    entity::Burger delivery;
};
}
