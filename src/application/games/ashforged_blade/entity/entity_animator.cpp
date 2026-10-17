#include "entity_animator.hpp"

// utilized on every state change
void EntityAnimator::resetFrameAndTimer() {
    this->currentFrame_ = 0;
    this->frameTimer_ = 0;
}
