#include "BeefPatty.hpp"
#include "singleton/Collision.hpp"

ingredient::BeefPatty::BeefPatty(glm::vec3 position) : Ingredient(position, glm::vec3(0.1), recipe::EIngredient::BEEFPATTY) {
    ComputeHitBoxes();
}

void ingredient::BeefPatty::Update(double delta) {}

Obj& ingredient::BeefPatty::GetObj() {
    static Obj obj("../../../data/ingredients/patty.obj");
    return obj;
}