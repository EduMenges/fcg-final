#include "Oven.hpp"

namespace model {
Obj& Oven::GetObj() {
    static Obj instance("../../../data/oven/fkc.obj", true);
    return instance;
}
}
