#include "BottomBun.hpp"
#include "singleton/Collision.hpp"

ingredient::BottomBun::BottomBun(glm::vec3 position) : Ingredient(position, glm::vec3(0.3)) {
    ComputeHitBoxes();
}

void ingredient::BottomBun::Update(double delta) {}

Obj& ingredient::BottomBun::GetObj() {
    static Obj obj("../../../data/ingredients/bottom_bun.obj");
    return obj;
}