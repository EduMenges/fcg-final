#pragma once

namespace trait {
class Updatable {
   public:
    virtual ~Updatable() = default;
    /**
     * Updates the implementer according to how much time elapsed.
     * @param delta Time elapsed between last cycle.
     */
    virtual void Update(double /* delta */){

    };

    /// To be used by updatables that overload @ref Update
    bool paused_ = false;
};
}
