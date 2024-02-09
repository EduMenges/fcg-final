#include "HeldObject.hpp"
#include "Camera.hpp"
#include "Entity.hpp"
#include "entity/ingredient/Ingredient.hpp"
#include "matrices.hpp"
#include "recipe/EIngredient.hpp"
#include "singleton/Input.hpp"
#include <iostream>
#include <numbers>

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

    object_->position_ = old_position_;
    object_->rotation_ = old_rotation_;
    object_            = nullptr;
}

void HeldObject::Update(double /*delta*/) {
    input::Mouse mouse = Input::Instance().mouse_;
    bool         grab  = Input::Instance().IsOn(GLFW_KEY_E);

    if (object_ == nullptr) {
        return;
    }

    glm::vec4 c_position = camera->GetCameraPosition();
    glm::vec4 view_vec   = camera->GetViewVec();
    glm::vec4 right_vec  = CrossProduct(view_vec, glm::vec4{0, 1, 0, 0});

    right_vec *= 0.2F;
    view_vec *= 0.5F;

    glm::vec4 held_position = c_position + view_vec + right_vec + glm::vec4{0, -0.15, 0, 0};

    float theta = glm::atan(view_vec.x, view_vec.z) + std::numbers::pi_v<float> / 2;

    object_->position_   = held_position;
    object_->rotation_.y = theta;

    if (mouse.M1 || grab) {
        ToBurger();
    }

    if (mouse.M2 || Input::Instance().IsOn(GLFW_KEY_Q)) {
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
    burger->ingredients_.clear();
    burger->is_complete_ = false;
    burger->y_offset_    = burger->GetHitBoxHeight();
    burger->AddIngredient(recipe::EIngredient::BOTTOMBUN);
}
