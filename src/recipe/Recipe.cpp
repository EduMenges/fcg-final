#include "EIngredient.hpp"
#include "Recipe.hpp"
#include <cstdlib>
#include <ctime>

namespace recipe {

// Define os ingredientes para uma dada receita
Recipe::Recipe(RecipeName recipe_name) : name(recipe_name) {
    switch (recipe_name) {
        case RecipeName::BLT:
            this->ingredients_ = {EIngredient::BOTTOMBUN, EIngredient::LETTUCE, EIngredient::TOMATO,
                                  EIngredient::BEEFPATTY, EIngredient::BACON,   EIngredient::MUSTARD,
                                  EIngredient::TOPBUN};
            break;

        case RecipeName::CHEESEBURGER:
            this->ingredients_ = {EIngredient::BOTTOMBUN, EIngredient::LETTUCE, EIngredient::BEEFPATTY,
                                  EIngredient::CHEESE,    EIngredient::KETCHUP, EIngredient::EGG,
                                  EIngredient::TOPBUN};
            break;

        case RecipeName::MEATLOVER:
            this->ingredients_ = {EIngredient::BOTTOMBUN, EIngredient::BEEFPATTY, EIngredient::BACON, EIngredient::EGG,
                                  EIngredient::BEEFPATTY, EIngredient::BACON,     EIngredient::TOPBUN};
            break;

        case RecipeName::SALAD:
            this->ingredients_ = {EIngredient::BOTTOMBUN, EIngredient::LETTUCE,   EIngredient::TOMATO,
                                  EIngredient::MUSTARD,   EIngredient::BEEFPATTY, EIngredient::KETCHUP,
                                  EIngredient::TOPBUN};
            break;

        case RecipeName::SPECIAL:
            this->ingredients_ = {EIngredient::BOTTOMBUN, EIngredient::CHEESE, EIngredient::BEEFPATTY,
                                  EIngredient::TOMATO,    EIngredient::BACON,  EIngredient::EGG,
                                  EIngredient::TOPBUN};
            break;
    }
}

// Aleatoriza uma receita
Recipe::Recipe() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    RecipeName randomRecipe = static_cast<RecipeName>(std::rand() % static_cast<int>(RecipeName::COUNT));
    *this                   = Recipe(randomRecipe);
}

}
