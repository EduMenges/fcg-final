#include "Ketchup.hpp"
#include "singleton/Collision.hpp"

ingredient::Ketchup::Ketchup(glm::vec3 position) : Ingredient(position, glm::vec3(0.04F), recipe::EIngredient::KETCHUP) {
    ComputeHitBoxes();
}

void ingredient::Ketchup::Update(double delta) {}

Obj& ingredient::Ketchup::GetObj() {
    static Obj obj("../../../data/ingredients/ketchup-splash.obj", false);
    return obj;
}