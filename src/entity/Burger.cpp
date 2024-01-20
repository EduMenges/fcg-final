#include "Burger.hpp"

entity::Burger::Burger(glm::vec3 position)
    : Entity(model::Obj("../../../data/hamburgeres/hamburgeres.obj", position, glm::vec3(1))) {}
