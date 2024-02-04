#include "HeldObject.hpp"
#include "Camera.hpp"
#include "Entity.hpp"
#include "entity/ingredient/Ingredient.hpp"
#include "matrices.hpp"
#include "recipe/EIngredient.hpp"
#include <iostream>



HeldObject::HeldObject(Camera* c, EntityContainer* ec): camera(c), entities(ec), object(nullptr), burger(nullptr) {}

void HeldObject::Set(ingredient::Ingredient& new_object) {
    if(object != nullptr){
        return;
    }
    Unset();
    object = &new_object;
    old_position = object->position_;
    old_rotation = object->rotation_;
}

void HeldObject::Unset() {
    if(object == nullptr) {
        return;
    }

    //std::cout<<entities->size()<<std::endl;
    //entities->remove_if([this](const auto& obj) { return obj.get() == object; }); 
    //std::cout<<"->"<<entities->size()<<std::endl;
    object->position_ = old_position;
    object->rotation_ = old_rotation;
    object = nullptr;
    
}
    
void HeldObject::Update(double delta) {
    input::Mouse mouse = Input::Instance().mouse_;

    if(object == nullptr) {
        return;
    }

    glm::vec4 c_position = camera->GetCameraPosition();
    glm::vec4 view_vec = camera->GetViewVec();
    glm::vec4 right_vec = CrossProduct(view_vec, glm::vec4{0,1,0,0});
    //glm::vec4 horizontal = glm::normalize(glm::vec4{view_vec.x, 0, view_vec.z, 0});

    right_vec *= 0.2;
    view_vec *= 0.5;

    glm::vec4 held_position = c_position + view_vec + right_vec + glm::vec4{0,-0.15,0,0};

    float theta = glm::atan(view_vec.x, view_vec.z) + 3.14/2;
    //float phi = glm::asin(view_vec.y/Norm(view_vec));  

    object->position_ = held_position;
    object->rotation_.y = theta;
    //glm::vec4 rotate4 = MatrixRotate(phi, horizontal) * glm::vec4{view};
    //object->rotation_ = glm::vec3{rotate4.x, theta, rotate4.z};
    //object->rotation_.x = phi;//0*phi*glm::cos(theta);
    //object->rotation_.z = phi;//*glm::sin(theta);

    //float dy = static_cast<float>(delta);
    //object->rotation_.y += dy;

    if(mouse.M1){
        ToBurger();
    }

    if(mouse.M2){
        Unset();
    }
}

void HeldObject::ToBurger() {
    if(object == nullptr)
        return;

    if(burger != nullptr) {
        recipe::EIngredient x = object->index;
        if(x != recipe::EIngredient::COUNT)
            burger->AddIngredient(x);
    }

    Unset();
}

void HeldObject::LinkBurger(entity::Burger& b) {
    burger = &b;
}
