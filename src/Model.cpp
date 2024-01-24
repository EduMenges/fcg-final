#include "Model.hpp"
void Model::Draw(Camera& c) {
    glm::mat4 model_matrix = MatrixTranslate(position_.x, position_.y, position_.z) *
                                                      MatrixScale(scale_.x, scale_.y, scale_.z) * MatrixRotateX(rotation_.x) *  //
                                                      MatrixRotateY(rotation_.y) *                                              //
                                                      MatrixRotateZ(rotation_.z);

    GetObj().Draw(c, model_matrix);
}
