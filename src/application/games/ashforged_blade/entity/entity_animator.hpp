#ifndef AION_ZERO_FMW_ENTITY_ANIMATOR_HPP
#define AION_ZERO_FMW_ENTITY_ANIMATOR_HPP

#include <cstdint>
#include <bits/range_access.h>

class EntityAnimator {
protected:
    uint8_t frameTimer_ = 0;
    uint8_t currentFrame_= 0;

    template<std::size_t N>
    void updateFrameAndTimer(const unsigned char* const (&frames)[N], uint8_t fps);

public:
    EntityAnimator() = default;

    void resetFrameAndTimer();
};


template<std::size_t N>
void EntityAnimator::updateFrameAndTimer(const unsigned char* const (&frames)[N], const uint8_t fps) {
    if (++this->frameTimer_ >= fps) {
        this->frameTimer_ = 0;
        this->currentFrame_ = (this->currentFrame_ + 1) % std::size(frames);
    }
}

#endif //AION_ZERO_FMW_ENTITY_ANIMATOR_HPP