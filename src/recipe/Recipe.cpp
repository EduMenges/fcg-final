#include "EIngredient.hpp"
#include "Recipe.hpp"
#include <cstdlib>
#include <ctime>

namespace recipe {

// Define os ingredientes para uma dada receita
Recipe::Recipe(RecipeName recipe_name) : name(recipe_name) {
    switch (recipe_name) {
        case RecipeName::BLT:
            this->ingredients_ = {EIngredient::kBottomBun, EIngredient::kLettuce, EIngredient::kTomato,
                                  EIngredient::kBeefPatty, EIngredient::kBacon,   EIngredient::kMustard,
                                  EIngredient::kTopBun};
            break;

        case RecipeName::CHEESEBURGER:
            this->ingredients_ = {EIngredient::kBottomBun, EIngredient::kLettuce, EIngredient::kBeefPatty,
                                  EIngredient::kCheese,    EIngredient::kKetchup, EIngredient::kEgg,
                                  EIngredient::kTopBun};
            break;

        case RecipeName::MEATLOVER:
            this->ingredients_ = {EIngredient::kBottomBun, EIngredient::kBeefPatty, EIngredient::kBacon,
                                  EIngredient::kEgg,       EIngredient::kBeefPatty, EIngredient::kBacon,
                                  EIngredient::kTopBun};
            break;

        case RecipeName::SALAD:
            this->ingredients_ = {EIngredient::kBottomBun, EIngredient::kLettuce,   EIngredient::kTomato,
                                  EIngredient::kMustard,   EIngredient::kBeefPatty, EIngredient::kKetchup,
                                  EIngredient::kTopBun};
            break;

        case RecipeName::SPECIAL:
            this->ingredients_ = {EIngredient::kBottomBun, EIngredient::kCheese, EIngredient::kBeefPatty,
                                  EIngredient::kTomato,    EIngredient::kBacon,  EIngredient::kEgg,
                                  EIngredient::kTopBun};
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
