#include "HeldObject.hpp"
#include "Camera.hpp"
#include "Entity.hpp"
#include "entity/ingredient/Ingredient.hpp"
#include "matrices.hpp"
#include "recipe/EIngredient.hpp"
#include <iostream>

HeldObject::HeldObject(Camera* c, EntityContainer* ec) : camera(c), entities(ec) {}

void HeldObject::Set(ingredient::Ingredient& new_object) {
    if (object_ != nullptr) {
        return;
    }
    Unset();
    object_       = &new_object;
    old_position_ = object_->position_;
    old_rotation_ = object_->rotation_;
}

void HeldObject::Unset() {
    if (object_ == nullptr) {
        return;
    }

    // std::cout<<entities->size()<<std::endl;
    // entities->remove_if([this](const auto& obj) { return obj.get() == object; });
    // std::cout<<"->"<<entities->size()<<std::endl;

    object_->position_ = old_position_;
    object_->rotation_ = old_rotation_;
    object_            = nullptr;
}

void HeldObject::Update(double delta) {
    input::Mouse mouse = Input::Instance().mouse_;

    if (object_ == nullptr) {
        return;
    }

    glm::vec4 c_position = camera->GetCameraPosition();
    glm::vec4 view_vec   = camera->GetViewVec();
    glm::vec4 right_vec  = CrossProduct(view_vec, glm::vec4{0, 1, 0, 0});
    // glm::vec4 horizontal = glm::normalize(glm::vec4{view_vec.x, 0, view_vec.z, 0});

    right_vec *= 0.2;
    view_vec *= 0.5;

    glm::vec4 held_position = c_position + view_vec + right_vec + glm::vec4{0, -0.15, 0, 0};

    float theta = glm::atan(view_vec.x, view_vec.z) + 3.14 / 2;
    // float phi = glm::asin(view_vec.y/Norm(view_vec));

    object_->position_   = held_position;
    object_->rotation_.y = theta;
    // glm::vec4 rotate4 = MatrixRotate(phi, horizontal) * glm::vec4{view};
    // object->rotation_ = glm::vec3{rotate4.x, theta, rotate4.z};
    // object->rotation_.x = phi;//0*phi*glm::cos(theta);
    // object->rotation_.z = phi;//*glm::sin(theta);

    // float dy = static_cast<float>(delta);
    // object->rotation_.y += dy;

    if (mouse.M1) {
        ToBurger();
    }

    if (mouse.M2) {
        Unset();
    }
}

void HeldObject::ToBurger() {
    if (object_ == nullptr || burger == nullptr || !(burger->IsBeingLooked(*camera))) {
        return;
    }

    if (object_->index_ != recipe::EIngredient::COUNT) {
        burger->AddIngredient(object_->index_);
    }
    

    Unset();
}

void HeldObject::LinkBurger(entity::Burger& b) { burger = &b; }

void HeldObject::ResetBurger() {
    /* while(burger->ingredients_.size() > 0) {
        std::cout << burger->ingredients_.size() << std::endl;
        burger->Pop();
        } */
    /* auto it = burger->ingredients_.begin();
    while(it != burger->ingredients_.end()) {
        it = burger->ingredients_.erase(it);
    } */

    //burger->is_complete_ = false;
    //burger->y_offset_ = burger->GetHitBoxHeight();
    //burger->AddIngredient(recipe::EIngredient::BOTTOMBUN);
}
