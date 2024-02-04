#pragma once

#include "Model.hpp"

namespace model {

class Cube : public Model {
   public:
    explicit Cube(glm::vec3 position, glm::vec3 scale = glm::vec3(1), glm::vec3 rotation = glm::vec3(0))
        : Model(position, scale, rotation) {

    };

    Obj& GetObj() override;
};

}
