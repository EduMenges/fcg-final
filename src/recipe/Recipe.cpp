#pragma once
#include "EIngredient.hpp"
#include "Recipe.hpp"
#include <cstdlib>

namespace recipe {

    // Define os ingredientes para uma dada receita
    Recipe::Recipe(RecipeName recipe_name) {

        switch(recipe_name) {
            case RecipeName::BLT:
                this->recipe = {EIngredient::BOTTOMBUN, EIngredient::LETTUCE, EIngredient::TOMATO,
                                EIngredient::BEEFPATTY, EIngredient::BACON, EIngredient::MUSTARD, EIngredient::TOPBUN};
                break;

            case RecipeName::CHEESEBURGER:
                this->recipe = {EIngredient::BOTTOMBUN, EIngredient::LETTUCE, EIngredient::BEEFPATTY,
                                EIngredient::CHEESE, EIngredient::KETCHUP, EIngredient::EGG, EIngredient::TOPBUN};
                break;

            case RecipeName::MEATLOVER:
                this->recipe = {EIngredient::BOTTOMBUN, EIngredient::BEEFPATTY, EIngredient::BACON,
                                EIngredient::EGG, EIngredient::BEEFPATTY, EIngredient::BACON, EIngredient::TOPBUN};
                break;

            case RecipeName::VEGAN:
                this->recipe = {EIngredient::BOTTOMBUN, EIngredient::LETTUCE, EIngredient::BEEFPATTY,
                                EIngredient::CHEESE, EIngredient::KETCHUP, EIngredient::BACON, EIngredient::TOPBUN};
                break;

            case RecipeName::SPECIAL:
                this->recipe = {EIngredient::BOTTOMBUN, EIngredient::LETTUCE, EIngredient::BEEFPATTY,
                                EIngredient::CHEESE, EIngredient::KETCHUP, EIngredient::BACON, EIngredient::TOPBUN};
                break;
        }
    }

    // Aleatoriza uma receita
    Recipe::Recipe() : Recipe(static_cast<RecipeName>(std::rand() % static_cast<int>(RecipeName::COUNT))) {
    }

}
