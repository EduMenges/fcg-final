#include "TopBun.hpp"
#include "singleton/Collision.hpp"

ingredient::TopBun::TopBun(glm::vec3 position) : Ingredient(position, glm::vec3(0.3)) {
    ComputeHitBoxes();
}

void ingredient::TopBun::Update(double delta) {}

Obj& ingredient::TopBun::GetObj() {
    static Obj obj("../../../data/ingredients/ketchup-splash.obj");
    return obj;
}