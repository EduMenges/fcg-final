#include "Order.hpp"

namespace recipe{

    Order::Order(Recipe recipe) : recipe(recipe) {};

    int Order::Score(entity::Burger burger) {
        int score = 0;

        std::vector<recipe::EIngredient> ingredients;
        for (const auto& ing : burger.ingredients) {
            ingredients.push_back(ing->index);
        }

        // Lógica principal:
        //   +100 pontos por ingrediente certo
        //   +50 pontos por ingrediente certo no lugar errado
        //   -100 pontos por ingrediente faltando
        //   -50 pontos por ingrediente sobrando
        //   +200 pontos para um pedido perfeito (?)



    }
}
