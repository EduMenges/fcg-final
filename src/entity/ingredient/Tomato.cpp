#include "Tomato.hpp"
#include "singleton/Collision.hpp"

ingredient::Tomato::Tomato(glm::vec3 position) : Ingredient(position, glm::vec3(0.1), recipe::EIngredient::TOMATO) {
    ComputeHitBoxes();
}

void ingredient::Tomato::Update(double delta) {}

Obj& ingredient::Tomato::GetObj() {
    static Obj obj("../../../data/ingredients/tomato.obj");
    return obj;
}