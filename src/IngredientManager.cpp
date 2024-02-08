#include "IngredientManager.hpp"
#include "Camera.hpp"
#include "input/Mouse.hpp"
#include "singleton/Input.hpp"

IngredientManager::IngredientManager(EntityContainer* ec, HeldObject* ho) : entities_(ec), held_object_(ho) {}

void IngredientManager::Init() {
    entities_->emplace_back(std::make_unique<ingredient::Lettuce>(glm::vec3{1.2, table_y, -2})); //
    lettuce_ref = dynamic_cast<ingredient::Lettuce*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Egg>(glm::vec3{-2, table_y, -0.7})); //
    egg_ref = dynamic_cast<ingredient::Egg*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Tomato>(glm::vec3{-1.2, table_y, -2})); //
    tomato_ref = dynamic_cast<ingredient::Tomato*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Bacon>(glm::vec3{2, table_y, -0.7})); //
    bacon_ref = dynamic_cast<ingredient::Bacon*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::Cheese>(glm::vec3{2, table_y, 0.7})); //
    cheese_ref = dynamic_cast<ingredient::Cheese*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::BeefPatty>(glm::vec3{-2, table_y, 0.7})); //
    beef_ref = dynamic_cast<ingredient::BeefPatty*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::TopBun>(glm::vec3{0, table_y, 2})); //
    bun_ref = dynamic_cast<ingredient::TopBun*>(entities_->back().get());

    entities_->emplace_back(std::make_unique<ingredient::KetchupBottle>(glm::vec3{1.2, table_y, 2})); 
    ketchup_ref = dynamic_cast<ingredient::KetchupBottle*>(entities_->back().get());
    ketchup_ref->rotation_.y = glm::radians(180.0F);

    entities_->emplace_back(std::make_unique<ingredient::MustardBottle>(glm::vec3{-1.2, table_y, 2})); 
    mustard_ref = dynamic_cast<ingredient::MustardBottle*>(entities_->back().get());
    mustard_ref->rotation_.y = glm::radians(180.0F);
}

void IngredientManager::Update(double /* delta */) {
    input::Mouse mouse = Input::Instance().mouse_;
    bool grab = Input::Instance().IsOn(GLFW_KEY_E);

    // No caso de clicar com M1 para pegar um ingrediente e não estar segurando nenhum
    if(held_object_->object_== nullptr && (mouse.M1 || grab)){
        Camera& camera = *(held_object_->camera);

        if(lettuce_ref->IsBeingLooked(camera)){
            held_object_->Set(*lettuce_ref);
        }

        else if(egg_ref->IsBeingLooked(camera)){
            held_object_->Set(*egg_ref);
        }

        else if(tomato_ref->IsBeingLooked(camera)){
            held_object_->Set(*tomato_ref);
        }

        else if(bacon_ref->IsBeingLooked(camera)){
            held_object_->Set(*bacon_ref);
        }
        
        else if(cheese_ref->IsBeingLooked(camera)){
            held_object_->Set(*cheese_ref);
        }

        else if(beef_ref->IsBeingLooked(camera)){
            held_object_->Set(*beef_ref);
        }

        else if(bun_ref->IsBeingLooked(camera)){
            held_object_->Set(*bun_ref);
        }

        else if(ketchup_ref->IsBeingLooked(camera)){
            held_object_->Set(*ketchup_ref);
        }

        else if(mustard_ref->IsBeingLooked(camera)){
            held_object_->Set(*mustard_ref);
        }
    }

}
