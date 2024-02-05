#include "Generic.hpp"

namespace model {

std::unordered_map<std::filesystem::path, Obj> Generic::map_{};

Generic::Generic(std::filesystem::path model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
    : Model(position, scale, rotation), model_(std::move(model)) {
    if (!map_.contains(model_)) {
        map_.emplace(model_, Obj(model_));
    }
}
}
