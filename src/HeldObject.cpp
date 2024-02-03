#pragma once
#include "HeldObject.hpp"



HeldObject::HeldObject(): object(nullptr) {}

void HeldObject::Set(Entity& new_object) {
    object = &new_object;
}
    
void HeldObject::Update(double delta) {
    input::Mouse mouse = Input::Instance().mouse_;

    if(mouse.M1)
        return;

    float dy = static_cast<float>(delta);
    object->rotation_.y += dy;
}
