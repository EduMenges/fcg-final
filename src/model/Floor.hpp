#pragma once
#include "Model.hpp"

namespace model {

class Floor: public Model {
   public:
    Floor() : Model({0.0F, 0.0F, 0.0F}, glm::vec3(0.05)) {}

    Obj& GetObj() override;
};

}