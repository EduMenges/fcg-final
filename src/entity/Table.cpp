#include "Table.hpp"
#include "singleton/Collision.hpp"

entity::Table::Table(glm::vec3 position) : Entity(position, glm::vec3(0.3), glm::vec3(0.0, 0.5, 0.0)) {
    ComputeHitBoxes();
}

Obj& entity::Table::GetObj() {
    static Obj obj("../../../data/table/table.obj");
    return obj;
}
