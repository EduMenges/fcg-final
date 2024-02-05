#pragma once

#include "Model.hpp"

namespace model {

class Oven : public Model {
   public:
    Oven(glm::vec3 position, glm::vec3 scale = glm::vec3(0.03F), glm::vec3 rotation = glm::vec3(0.0F))
        : Model(position, scale, rotation) {
        ComputeHitBoxes();
    }

    Obj& GetObj() override;
};

}
