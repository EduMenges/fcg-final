#include "MustardBottle.hpp"
#include "singleton/Collision.hpp"

ingredient::MustardBottle::MustardBottle(glm::vec3 position)
    : Ingredient(position, glm::vec3(0.12), recipe::EIngredient::kMustard) {
    ComputeHitBoxes();
}

void ingredient::MustardBottle::Update(double delta) {}

Obj& ingredient::MustardBottle::GetObj() {
    static Obj obj("../../../data/condiments/mustard.obj");
    return obj;
}
