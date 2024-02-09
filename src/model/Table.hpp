#pragma once

#include "Model.hpp"
#include "Entity.hpp"

namespace model {

class Table : public Model {
   public:
    explicit Table(glm::vec3 position);

    Obj& GetObj() override;
};

}
