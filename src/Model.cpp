#include "Model.hpp"
#include "singleton/Collision.hpp"
#include <algorithm>

void Model::Draw(Camera& c) {
    glm::mat4 model_matrix = GetTransform();

    GetObj().Draw(c, model_matrix);
}

void Model::ComputeHitBoxes() {
    for (auto box : GetObj().boxes_) {
        glm::mat4 transform = GetTransform();

        HitBox hb(transform * (glm::vec4(box.min_, 1.0)), transform * (glm::vec4(box.max_, 1.0)));
        hb.AdjustValues();

        AddHitBox(hb);
    }
}

void Model::AddHitBox(HitBox hb) {
    auto& location = hit_boxes_.emplace_back(hb);
    Collision::Instance().AddBox(&location);
}

float Model::GetHitBoxHeight() {
    float max_dy = 0;

    for (const HitBox& hb : this->hit_boxes_) {
        max_dy = std::max(max_dy, hb.max_.y - hb.min_.y);
    }

    return max_dy;
}

glm::mat4 Model::GetTransform() const {
    return MatrixTranslate(position_) *  //
           MatrixScale(scale_) *         //
           MatrixRotateX(rotation_.x) *  //
           MatrixRotateY(rotation_.y) *  //
           MatrixRotateZ(rotation_.z);
}
