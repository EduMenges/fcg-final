#include "Order.hpp"
#include "EIngredient.hpp"

namespace recipe{

    Order::Order(Recipe recipe) : recipe_ref(recipe) {};

    int Order::Score(entity::Burger* burger) {
        int score = 0;

        std::vector<recipe::EIngredient> recipe = recipe_ref.recipe;
        std::vector<recipe::EIngredient> ingredients;
        for (const auto& ing : burger->ingredients_) {
            ingredients.push_back(ing->index_);
        }

        // Lógica principal:
        //   +100 pontos por ingrediente certo
        //   +50 pontos por ingrediente certo no lugar errado
        //   -100 pontos por ingrediente faltando
        //   -50 pontos por ingrediente sobrando
        //   +200 pontos para um pedido perfeito (?)

        for(int i_burger = 0; i_burger < ingredients.size(); i_burger++) {
            bool found_match = false;

            for(int i_recipe = 0; i_recipe < recipe.size(); i_recipe++) {
                if(recipe[i_recipe] == ingredients[i_burger]) { // Se encontrou uma correspondência
                    found_match = true;
                    score += 50;
                    if(i_recipe == i_burger) {
                        score += 50;
                    }
                    recipe[i_recipe] = recipe::EIngredient::COUNT; // Anula ingrediente para contagem
                    break;
                }
            }
            ingredients[i_burger] = recipe::EIngredient::COUNT;
            if(!found_match) {
                score -= 50; // Ingrediente sobrando
            }
        }

        // Verifica ingredientes faltando
        for(int i = 0; i < recipe.size(); i++) {
            if(recipe[i] != recipe::EIngredient::COUNT) {
                score -= 100;
            }
        }

        // Bônus de pontuação
        if(score == 100*recipe.size()){
            score += 200;
        }

        return score;
    }
}
