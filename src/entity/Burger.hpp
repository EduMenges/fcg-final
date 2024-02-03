#pragma once

//#include "Entity.hpp"
#include "ingredient/Ingredient.hpp"
#include <vector>
#include <memory>

namespace entity {

class Burger : public Entity {
   public:
    explicit Burger(glm::vec3 position);

    std::vector<std::unique_ptr<ingredient::Ingredient>> ingredients = {};
    float yOffset;
    bool isComplete;

    void Update(double delta) override;

    void Draw(Camera& c) override; 

    void AddIngredient(recipe::EIngredient index);

    std::unique_ptr<ingredient::Ingredient> GetIngredientByIndex(recipe::EIngredient index);

    Obj& GetObj() override;
};

}