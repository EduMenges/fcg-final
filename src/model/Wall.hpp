#include "Model.hpp"

namespace model {

class Wall : public Model {
   public:
    explicit Wall(glm::vec3 position, glm::vec3 scale = glm::vec3(1.0F), glm::vec3 rotation = glm::vec3(0.0F))
        : Model(position, scale, rotation) {
        ComputeHitBoxes();
    }

    Obj& GetObj() override;
};

}
