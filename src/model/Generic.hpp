#pragma once

#include "Model.hpp"

namespace model {
class Generic : public Model {
   public:
    Generic(std::filesystem::path model, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0F),
            glm::vec3 rotation = glm::vec3(0.0F));

    Obj& GetObj() override { return map_.at(model_); }

   private:
    std::filesystem::path                                 model_;
    static std::unordered_map<std::filesystem::path, Obj> map_;
};
}
