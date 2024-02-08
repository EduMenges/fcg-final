#pragma once

// #include "Entity.hpp"
#include "ingredient/Ingredient.hpp"
#include <list>
#include <memory>
#include "CubicBezier.hpp"

namespace entity {

class Burger : public Entity {
   public:
    explicit Burger(glm::vec3 position);
    bool is_complete_ = false; // Indica se ainda pode receber ingredientes;

    bool is_correct_ = false;
    bool is_traveling_ = false;

    CubicBezier bezier_{{position_, glm::vec3{2,1,-6}, glm::vec3{3,3,4}, glm::vec3{2, 2, 8}}, 10, false};

    HitSphere sphere_{position_, 0.1};

    void Update(double delta) override;

    void Draw(Camera& c) override;

    void AddIngredient(recipe::EIngredient index);

    std::unique_ptr<ingredient::Ingredient> GetIngredientByIndex(recipe::EIngredient index);

    Obj& GetObj() override;

    std::list<std::unique_ptr<ingredient::Ingredient>> ingredients_ = {};
    float                                                y_offset_;

};

}
