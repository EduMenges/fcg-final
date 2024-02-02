#include "Lettuce.hpp"
#include "singleton/Collision.hpp"

ingredient::Lettuce::Lettuce(glm::vec3 position) : Ingredient(position, glm::vec3(0.3)) {
    ComputeHitBoxes();
}

void ingredient::Lettuce::Update(double delta) {}

Obj& ingredient::Lettuce::GetObj() {
    static Obj obj("../../../data/ingredients/ketchup-splash.obj");
    return obj;
}