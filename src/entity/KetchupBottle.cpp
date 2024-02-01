#include "KetchupBottle.hpp"
#include "singleton/Collision.hpp"
#include "singleton/Input.hpp"

entity::KetchupBottle::KetchupBottle(glm::vec3 position) : Entity(position, glm::vec3(0.2)), normal_position(position){

    //this->normal_position = position;

    for (size_t i = 0; i < GetObj().bbox_min_.size(); ++i) {
        glm::vec3 bbox_min = GetObj().bbox_min_[i] * scale_;
        glm::vec3 bbox_max = GetObj().bbox_max_[i] * scale_;

        HitBox hb(bbox_min + position_, bbox_max + position_);
        AddHitBox(hb);
    }
}

void entity::KetchupBottle::Update(double delta) { 
    printf("%f\n", this->normal_position.y);

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
