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
    float min_y = std::numeric_limits<float>::max();
    float max_y = -std::numeric_limits<float>::max();

    for (HitBox hb : hit_boxes_) {
        min_y = std::min(min_y, hb.min_.y);
        max_y = std::max(max_y, hb.max_.y);
    }

    return max_y - min_y;
}

glm::mat4 Model::GetTransform() const {
    return MatrixTranslate(position_) *  //
           MatrixScale(scale_) *         //
           MatrixRotateX(rotation_.x) *  //
           MatrixRotateY(rotation_.y) *  //
           MatrixRotateZ(rotation_.z);
}

void Model::RemoveHitBoxes() {
    for (auto& hb : hit_boxes_) {
        Collision::Instance().RemoveBox(&hb);
    }
    hit_boxes_.clear();
}

Model::~Model() { RemoveHitBoxes(); }

HitBox Model::GetBoundingBox() {
    auto   it = hit_boxes_.begin();
    HitBox bb = *it;
    it++;

    for (; it != hit_boxes_.end(); ++it) {
        bb = {glm::min(bb.min_, it->min_), glm::max(bb.max_, it->max_)};
    }

    return bb;
}
