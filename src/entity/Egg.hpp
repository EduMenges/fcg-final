#pragma once

#include "Entity.hpp"

namespace entity {

class Egg : public Entity {
   public:
    explicit Egg(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}