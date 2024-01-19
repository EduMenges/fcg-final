#include "Burger.hpp"

entity::Burger::Burger(glm::vec3 position): Entity(model::Obj("../../../data/hamburgueres", position, glm::vec3(1))) {}
