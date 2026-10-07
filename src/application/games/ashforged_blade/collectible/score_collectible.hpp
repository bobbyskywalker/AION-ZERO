#ifndef AION_ZERO_FMW_SCORE_COLLECTIBLE_HPP
#define AION_ZERO_FMW_SCORE_COLLECTIBLE_HPP

#include "base_collectible.hpp"
#include <cstdint>

class ScoreCollectible : public BaseCollectible {
private:

    static constexpr const unsigned char *sprite = nullptr;

public:
    explicit ScoreCollectible(uint16_t initialX, uint16_t initialY);

    void draw() const override;

    static constexpr uint16_t SCORE_VALUE = 25;
};

#endif //AION_ZERO_FMW_SCORE_COLLECTIBLE_HPP