#include "Lettuce.hpp"
#include "singleton/Collision.hpp"

ingredient::Lettuce::Lettuce(glm::vec3 position) : Ingredient(position, glm::vec3(0.13), recipe::EIngredient::LETTUCE) {
    ComputeHitBoxes();
}

void ingredient::Lettuce::Update(double delta) {}

Obj& ingredient::Lettuce::GetObj() {
    static Obj obj("../../../data/ingredients/lettuce.obj");
    return obj;
}