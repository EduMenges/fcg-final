#include "Burger.hpp"

entity::Burger::Burger(glm::vec3 position) : Entity(position, glm::vec3(0.01)) {}

void entity::Burger::Update(double delta) { rotation_.y += static_cast<float>(delta); }

Obj& entity::Burger::GetObj() {
    static Obj obj("../../../data/bush/jungle_bush01.obj");
    return obj;
}
