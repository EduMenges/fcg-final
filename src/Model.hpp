#pragma once

#include "Camera.hpp"
#include "Obj.hpp"
#include "glm/gtx/intersect.hpp"
#include "matrices.hpp"

class Model {
   public:
    explicit Model(glm::vec3 position, glm::vec3 scale = glm::vec3(1), glm::vec3 rotation = glm::vec3(0))
        : position_(position), scale_(scale), rotation_(rotation) {}

    Model(Model&& other) = default;

    Model(const Model& other) = delete;

    virtual ~Model();

    virtual void Draw(Camera& c);

    virtual Obj& GetObj() = 0;

    [[nodiscard]] glm::mat4 GetTransform() const;

    void ComputeHitBoxes();

    void AddHitBox(HitBox hb);

    /// Removes all the hitboxes registered in the singleton. Used in the destructor.
    void RemoveHitBoxes();

    float GetHitBoxHeight();

    HitBox GetBoundingBox();

    [[nodiscard]] bool IsBeingLooked(const Camera& camera, float radius = 0.4F) const {
        // How distant we are from this model. Might be used later.
        float distance;
        bool  intersects = glm::intersectRaySphere(camera.GetCameraPosition(), camera.GetViewVec(),
                                                   glm::vec4(position_, 1.0F), std::pow(radius, 2.0F), distance);

        return intersects && (distance <= 2.0F);
    }

    glm::vec3 position_;
    glm::vec3 scale_{1};
    glm::vec3 rotation_{0};

    std::vector<HitBox> hit_boxes_;
};
