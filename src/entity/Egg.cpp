#include "Egg.hpp"
#include "singleton/Collision.hpp"

entity::Egg::Egg(glm::vec3 position){};

void entity::Egg::Update(double delta) {};

Obj& entity::Table::GetObj() {
    static Obj obj("../../../data/ingredients/egg_fried.obj");
    return obj;
}