#include "Screen.hpp"
#include <map>

entity::Screen::Screen(glm::vec3 position, recipe::RecipeName recipe)
    : Entity(position, glm::vec3{0.4}), recipe(recipe) {
    ComputeHitBoxes();
}

void entity::Screen::Update(double delta) {}

void entity::Screen::Draw(Camera& c) { Model::Draw(c); }

Obj& entity::Screen::GetObj() {
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
    }
}

Obj& entity::Screen::BLT() {
    static Obj obj("../../../data/screen/blt.obj");
    return obj;
}

Obj& entity::Screen::Cheeseburger() {
    static Obj obj("../../../data/screen/cheeseburger.obj");
    return obj;
}

Obj& entity::Screen::Salad() {
    static Obj obj("../../../data/screen/salad.obj");
    return obj;
}

Obj& entity::Screen::Meatlover() {
    static Obj obj("../../../data/screen/meatlover.obj");
    return obj;
}

Obj& entity::Screen::Special() {
    static Obj obj("../../../data/screen/special.obj");
    return obj;
}
