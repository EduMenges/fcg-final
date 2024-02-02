#pragma once

#include "Entity.hpp"

namespace entity {

class MustardBottle : public Entity {
   public:
    explicit MustardBottle(glm::vec3 position);
    glm::vec3 normal_position;

    void Update(double delta) override;

    Obj& GetObj() override;
};

}