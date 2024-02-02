#include "Mustard.hpp"
#include "singleton/Collision.hpp"

ingredient::Mustard::Mustard(glm::vec3 position) : Ingredient(position, glm::vec3(0.3)) {
    ComputeHitBoxes();
}

void ingredient::Mustard::Update(double delta) {}

Obj& ingredient::Mustard::GetObj() {
    static Obj obj("../../../data/ingredients/mustard-splash.obj");
    return obj;
}