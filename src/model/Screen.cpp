#include "Screen.hpp"
#include <map>

model::Screen::Screen(glm::vec3 position, recipe::RecipeName recipe) : Model(position, glm::vec3{0.4}), recipe(recipe) {
    ComputeHitBoxes();
}

void model::Screen::Draw(Camera& c) { Model::Draw(c); }

Obj& model::Screen::GetObj() {
    switch (recipe) {
        case recipe::RecipeName::BLT:
            return BLT();

        case recipe::RecipeName::CHEESEBURGER:
            return Cheeseburger();

        case recipe::RecipeName::SALAD:
            return Salad();

        case recipe::RecipeName::MEATLOVER:
            return Meatlover();

        case recipe::RecipeName::SPECIAL:
            return Special();

        default:
            throw std::out_of_range("Recipe not registered");
    }
}

Obj& model::Screen::BLT() {
    static Obj obj("../../../data/screen/blt.obj");
    return obj;
}

Obj& model::Screen::Cheeseburger() {
    static Obj obj("../../../data/screen/cheeseburger.obj");
    return obj;
}

Obj& model::Screen::Salad() {
    static Obj obj("../../../data/screen/salad.obj");
    return obj;
}

Obj& model::Screen::Meatlover() {
    static Obj obj("../../../data/screen/meatlover.obj");
    return obj;
}

Obj& model::Screen::Special() {
    static Obj obj("../../../data/screen/special.obj");
    return obj;
}
