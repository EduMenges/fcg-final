#pragma once

#include "Entity.hpp"
#include "recipe/Recipe.hpp"

namespace entity {

    class Screen: public Entity {
        public:
          explicit Screen(glm::vec3 position, recipe::RecipeName recipe);
          recipe::RecipeName recipe;

          void Update(double delta) override;

          void Draw(Camera& c) override;

          Obj& GetObj() override;

          Obj& BLT();
    };

}