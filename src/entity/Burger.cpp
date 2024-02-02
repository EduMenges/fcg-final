#include "Burger.hpp"
#include "singleton/Collision.hpp"
#include "ingredient/Egg.hpp"
#include "ingredient/Mustard.hpp"

entity::Burger::Burger(glm::vec3 position) : Entity(position, glm::vec3(0.1)) {
    ComputeHitBoxes();
    this->ingredients.push_back(std::make_unique<ingredient::Egg>(position+glm::vec3{0, .25, 0}));
    this->ingredients.push_back(std::make_unique<ingredient::Mustard>(position+glm::vec3{0, .5, 0}));
}

void entity::Burger::Update(double delta) { rotation_.y += static_cast<float>(delta); }

Obj& entity::Burger::GetObj() {
    static Obj obj("../../../data/ingredients/cheese.obj");
    return obj;
}

void entity::Burger::Draw(Camera& c) {
    Model::Draw(c);
    for(const std::unique_ptr<ingredient::Ingredient>& ing : this->ingredients)
        ing->Draw(c);
}