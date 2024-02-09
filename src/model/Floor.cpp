#include "Floor.hpp"

namespace model {
Obj& Floor::GetObj() {
    static Obj instance("../../../data/floor/Floor.obj");
    return instance;
}
}
