#include "FlyingKetchup.hpp"

void entity::FlyingKetchup::Update(double delta) {
    bezier_.Update(delta);
    position_ = bezier_.Get();
}

Obj& entity::FlyingKetchup::GetObj() {
    static Obj obj("../../../data/condiments/ketchup.obj");
    return obj;
}
