#pragma once
#include "Ingredient.hpp"
#include <vector>
#include <iostream>
#include <string>

namespace recipe {
enum class RecipeName : int {  
    BLT = 0,
    CHEESEBURGER = 1,
    VEGAN = 2,
    MEATLOVER = 3,
    SPECIAL = 4,
    COUNT = 5
};

class Recipe {
    
    public:
      explicit Recipe(RecipeName recipe_name);
      explicit Recipe();
      std::vector<Ingredient> recipe;
      
};

}
