#include "Screen.hpp"
#include <map>

entity::Screen::Screen(glm::vec3 position, recipe::RecipeName recipe) : Entity(position, glm::vec3{0.4}), recipe(recipe) {
    ComputeHitBoxes();
}

void entity::Screen::Update(double delta) {}

void entity::Screen::Draw(Camera& c) {
    Model::Draw(c);
}

Obj& entity::Screen::GetObj() {
    switch(recipe) {
        case recipe::RecipeName::BLT:
            return BLT();
    }
}

Obj& entity::Screen::BLT() {
    static Obj obj("../../../data/screen/blt.obj");
    return obj;
}