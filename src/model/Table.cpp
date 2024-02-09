#include "Table.hpp"

model::Table::Table(glm::vec3 position) : Model(position, glm::vec3(0.3F)) { ComputeHitBoxes(); }

Obj& model::Table::GetObj() {
    static Obj obj("../../../data/table/table.obj", true);
    return obj;
}
