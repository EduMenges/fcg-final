#pragma once

#include "Entity.hpp"

namespace entity {

class Table : public Entity {
   public:
    explicit Table(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}