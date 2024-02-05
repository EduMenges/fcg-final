#pragma once
#include "EIngredient.hpp"
#include <vector>

namespace recipe {
enum class RecipeName : int { BLT = 0, CHEESEBURGER = 1, SALAD = 2, MEATLOVER = 3, SPECIAL = 4, COUNT = 5 };

class Recipe {
   public:
    Recipe();

    explicit Recipe(RecipeName recipe_name);
    RecipeName name;

    std::vector<EIngredient> ingredients_;
};
}
