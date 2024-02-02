#include "Bacon.hpp"
#include "singleton/Collision.hpp"

ingredient::Bacon::Bacon(glm::vec3 position) : Ingredient(position, glm::vec3(0.3)) {
    ComputeHitBoxes();
}

void ingredient::Bacon::Update(double delta) {}

Obj& ingredient::Bacon::GetObj() {
    static Obj obj("../../../data/ingredients/bacon.obj");
    return obj;
}