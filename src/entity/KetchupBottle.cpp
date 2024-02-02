#include "KetchupBottle.hpp"
#include "singleton/Collision.hpp"
#include "singleton/Input.hpp"

entity::KetchupBottle::KetchupBottle(glm::vec3 position) : Entity(position, glm::vec3(0.2)), normal_position(position){
    ComputeHitBoxes();
}

void entity::KetchupBottle::Update(double delta) { 

    input::Mouse mouse = Input::Instance().mouse_;
    if(! mouse.M1)
        this->position_ = this->normal_position;

    else {
        this->position_ = this->normal_position + glm::vec3(0,1,0);
    }

    
}

Obj& entity::KetchupBottle::GetObj() {
    static Obj obj("../../../data/condiments/ketchup.obj");
    return obj;
}
