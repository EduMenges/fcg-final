#include "Tomato.hpp"
#include "singleton/Collision.hpp"

ingredient::Tomato::Tomato(glm::vec3 position) : Ingredient(position, glm::vec3(0.1)) {
    ComputeHitBoxes();
}

void ingredient::Tomato::Update(double delta) {}

Obj& ingredient::Tomato::GetObj() {
    static Obj obj("../../../data/ingredients/ketchup-splash.obj");
    return obj;
}