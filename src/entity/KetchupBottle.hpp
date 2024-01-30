#pragma once

#include "Entity.hpp"

namespace entity {

class KetchupBottle : public Entity {
   public:
    explicit KetchupBottle(glm::vec3 position);

    void Update(double delta) override;

    Obj& GetObj() override;
};

}