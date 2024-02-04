#include "Wall.hpp"

namespace model {
Obj& Wall::GetObj() {
    static Obj instance("../../../data/wall/wall.obj");
    return instance;
}
}
