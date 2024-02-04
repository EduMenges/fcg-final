#include "Egg.hpp"
#include "singleton/Collision.hpp"

ingredient::Egg::Egg(glm::vec3 position) : Ingredient(position, glm::vec3(0.1), recipe::EIngredient::EGG) {
    ComputeHitBoxes();
}

void ingredient::Egg::Update(double delta) {}

Obj& ingredient::Egg::GetObj() {
    static Obj obj("../../../data/ingredients/egg_fried.obj");
    return obj;
}