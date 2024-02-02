#pragma once
#include "Ingredient.hpp"
#include "Recipe.hpp"
#include <cstdlib>

namespace recipe {

    // Define os ingredientes para uma dada receita
    Recipe::Recipe(RecipeName recipe_name) {

        switch(recipe_name) {
            case RecipeName::BLT:
                this->recipe = {Ingredient::BOTTOMBUN, Ingredient::LETTUCE, Ingredient::TOMATO,
                                Ingredient::BEEFPATTY, Ingredient::BACON, Ingredient::MUSTARD, Ingredient::TOPBUN};
                break;

            case RecipeName::CHEESEBURGER:
                this->recipe = {Ingredient::BOTTOMBUN, Ingredient::LETTUCE, Ingredient::BEEFPATTY,
                                Ingredient::CHEESE, Ingredient::KETCHUP, Ingredient::EGG, Ingredient::TOPBUN};
                break;

            case RecipeName::MEATLOVER:
                this->recipe = {Ingredient::BOTTOMBUN, Ingredient::BEEFPATTY, Ingredient::BACON,
                                Ingredient::EGG, Ingredient::BEEFPATTY, Ingredient::BACON, Ingredient::TOPBUN};
                break;

            case RecipeName::VEGAN:
                this->recipe = {Ingredient::BOTTOMBUN, Ingredient::LETTUCE, Ingredient::BEEFPATTY,
                                Ingredient::CHEESE, Ingredient::KETCHUP, Ingredient::BACON, Ingredient::TOPBUN};
                break;

            case RecipeName::SPECIAL:
                this->recipe = {Ingredient::BOTTOMBUN, Ingredient::LETTUCE, Ingredient::BEEFPATTY,
                                Ingredient::CHEESE, Ingredient::KETCHUP, Ingredient::BACON, Ingredient::TOPBUN};
                break;
        }
    }

    // Aleatoriza uma receita
    Recipe::Recipe() : Recipe(static_cast<RecipeName>(std::rand() % static_cast<int>(RecipeName::COUNT))) {
    }

}
