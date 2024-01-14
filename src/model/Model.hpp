#pragma once

class Model {
   public:
    virtual ~Model() = default;

    virtual void Update(float delta) {}

    virtual void Draw(Camera& c) {}

    bool paused = false;
};
