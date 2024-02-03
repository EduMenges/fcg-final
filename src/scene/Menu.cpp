#include "Menu.hpp"
#include "entity/Burger.hpp"
#include "entity/Table.hpp"
#include "entity/KetchupBottle.hpp"

#include "entity/MustardBottle.hpp"
#include "entity/ingredient/IngredientImports.hpp"
#include "Player.hpp"
#include "singleton/Input.hpp"
#include <iostream>



scene::Menu::Menu() : Scene({}, {}) {
    std::unique_ptr<entity::Table> table = std::make_unique<entity::Table>(glm::vec3{3, .8, 2});
    held_object_.Set(*table);
    float table_height = table->GetHitboxHeight();
    std::cout << table_height <<std::endl;
    glm::vec3 burger_pos = table->position_;// + glm::vec3{0,table->GetHitboxHeight(),0};
    burger_pos.y += 1.23*table_height;
    entities_.emplace_back(std::move(table));
    entities_.emplace_back(std::make_unique<entity::Burger>(burger_pos));
    //entities_.emplace_back(std::make_unique<ingredient::Cheese>(glm::vec3{4, 1.7, 2}));

    player_.SetPosition({3.0F, 2.0F, 3.5F, 1.0F});
    camera_->SetRotation({-2.45, 0.45});
    
}
