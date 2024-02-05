#pragma once
#include "Model.hpp"

namespace model {

class Floor : public Model {
   public:
    Floor(glm::vec3 position = glm::vec3(0.0F), glm::vec3 rotation = glm::vec3(0.0F))
        : Model(position, glm::vec3(0.05F), rotation) {}

    Obj& GetObj() override;
};

}
