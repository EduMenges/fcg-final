#pragma once

//#include "Entity.hpp"
#include "ingredient/Ingredient.hpp"
#include <vector>

namespace entity {

class Burger : public Entity {
   public:
    explicit Burger(glm::vec3 position);

    std::vector<std::unique_ptr<ingredient::Ingredient>> ingredients = {};

    void Update(double delta) override;

    void Draw(Camera& c) override;

    Obj& GetObj() override;
};

}