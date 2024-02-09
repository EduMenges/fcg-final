#include "BottomBun.hpp"
#include "singleton/Collision.hpp"

ingredient::BottomBun::BottomBun(glm::vec3 position)
    : Ingredient(position, glm::vec3(0.13), recipe::EIngredient::kBottomBun) {
    ComputeHitBoxes();
}

void ingredient::BottomBun::Update(double delta) {}

Obj& ingredient::BottomBun::GetObj() {
    static Obj obj("../../../data/ingredients/bottom_bun.obj");
    return obj;
}
