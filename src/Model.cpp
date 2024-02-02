#include "Model.hpp"
#include "singleton/Collision.hpp"
#include <algorithm>

void Model::Draw(Camera& c) {
    glm::mat4 model_matrix = MatrixTranslate(position_) *  //
                             MatrixScale(scale_) *         //
                             MatrixRotateX(rotation_.x) *  //
                             MatrixRotateY(rotation_.y) *  //
                             MatrixRotateZ(rotation_.z);

    GetObj().Draw(c, model_matrix);
}

void Model::ComputeHitBoxes() {
    for (auto box : GetObj().boxes_) {
        glm::mat4 transform = MatrixTranslate(position_) *  //
                              MatrixScale(scale_) *         //
                              MatrixRotateX(rotation_.x) *  //
                              MatrixRotateY(rotation_.y) *  //
                              MatrixRotateZ(rotation_.z);

        HitBox hb(transform * (glm::vec4(box.min_, 1.0)), transform * (glm::vec4(box.max_, 1.0)));
        hb.AdjustValues();

        AddHitBox(hb);
    }
}

void Model::AddHitBox(HitBox hb) {
    auto& location = hit_boxes_.emplace_back(hb);
    Collision::Instance().AddBox(&location);
}

float Model::GetHitboxHeight() {
    float maxY = 0;
    for (const HitBox& hb: this->hit_boxes_)
        maxY = std::max(maxY, hb.max_.y);
    return maxY;
}
