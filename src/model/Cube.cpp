#include "Cube.hpp"

namespace model {
Obj& Cube::GetObj() {
    static Obj instance("../../../data/cube/Crate1.obj");
    return instance;
}
}
