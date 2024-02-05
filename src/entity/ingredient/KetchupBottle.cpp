#include "KetchupBottle.hpp"
#include "singleton/Collision.hpp"

ingredient::KetchupBottle::KetchupBottle(glm::vec3 position) : Ingredient(position, glm::vec3(0.12), recipe::EIngredient::KETCHUP){
    ComputeHitBoxes();
}

void ingredient::KetchupBottle::Update(double delta) { }

Obj& ingredient::KetchupBottle::GetObj() {
    static Obj obj("../../../data/condiments/ketchup.obj");
    return obj;
}
