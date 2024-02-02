#include "Cheese.hpp"
#include "singleton/Collision.hpp"

ingredient::Cheese::Cheese(glm::vec3 position) : Ingredient(position, glm::vec3(0.3)) {
    ComputeHitBoxes();
}

void ingredient::Cheese::Update(double delta) {}

Obj& ingredient::Cheese::GetObj() {
    static Obj obj("../../../data/ingredients/cheese.obj");
    return obj;
}