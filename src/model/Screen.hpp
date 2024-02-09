#pragma once

#include "Model.hpp"
#include "recipe/Recipe.hpp"

namespace model {

class Screen : public Model {
   public:
    explicit Screen(glm::vec3 position, recipe::RecipeName recipe);

    void Draw(Camera& c) override;

    Obj& GetObj() override;

    static Obj& BLT();
    static Obj& Cheeseburger();
    static Obj& Salad();
    static Obj& Meatlover();
    static Obj& Special();

    recipe::RecipeName recipe;
};

}
