#ifndef AION_ZERO_FMW_HEALTH_COLLECTIBLE_HPP
#define AION_ZERO_FMW_HEALTH_COLLECTIBLE_HPP

#include "base_collectible.hpp"
#include "collectible_assets.hpp"

class HealthCollectible : public BaseCollectible {
private:

    static constexpr const unsigned char *sprite = CollectibleAssets::HEALTH_COLLECTIBLE;

public:
    explicit HealthCollectible(uint16_t initialX, uint16_t initialY);

    void draw() override;

    static constexpr uint16_t HEALTH_VALUE = 25;
};

#endif //AION_ZERO_FMW_HEALTH_COLLECTIBLE_HPP