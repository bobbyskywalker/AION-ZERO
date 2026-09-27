#ifndef AION_ZERO_FMW_ENEMY_HPP
#define AION_ZERO_FMW_ENEMY_HPP

#include <cstdint>

#include "../base_entity.hpp"
#include "enemy_assets.hpp"

class Enemy : public BaseEntity {
private:
    [[nodiscard]] bool isInCameraView() const;
    static constexpr uint8_t STEP_SIZE = TILE_SQ_SIZE / 8;

    static constexpr uint16_t MAX_HEALTH = 100;

public:
    explicit Enemy(
        uint16_t initialX,
        uint16_t initialY,
        uint16_t initialHealth,
        BaseMap & map
    );

    void draw() override;
    void followPlayer(uint16_t playerPosX);
};


#endif //AION_ZERO_FMW_ENEMY_HPP