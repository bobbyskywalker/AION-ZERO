#ifndef AION_ZERO_FMW_BASE_ENTITY_HPP
#define AION_ZERO_FMW_BASE_ENTITY_HPP

#include <cstdint>
#include "../maps/lvl_1.hpp"

class BaseEntity {
protected:
    BaseMap * map_;

    uint16_t health_;

    uint16_t posX_;
    uint16_t posY_;
    uint16_t cameraPosX_{};

    static constexpr uint8_t HEALTH_BAR_ABOVE_ENTITY_OFFSET = 2;
    static constexpr uint8_t HEALTH_BAR_HEIGHT = 2;
    static constexpr uint16_t HEALTH_BAR_WIDTH = ENTITY_SQ_SIZE;

public:
    explicit BaseEntity(
        const uint16_t initialX,
        const uint16_t initialY,
        const uint16_t initialHealth,
        BaseMap * map
    ) : map_(map), health_(initialHealth), posX_(initialX), posY_(initialY) {}
    virtual ~BaseEntity() = default;

    virtual void draw() = 0;

    void drawHealthBar(const uint16_t currentHealth, const uint16_t maxHealth, const uint16_t color) const {
        const uint16_t currentWidth = currentHealth * HEALTH_BAR_WIDTH / maxHealth;
        const uint16_t lostWidth = HEALTH_BAR_WIDTH - currentWidth;

        const uint16_t xStart = posX_ - cameraPosX_;
        const uint16_t yStart = posY_ - HEALTH_BAR_ABOVE_ENTITY_OFFSET;
        const uint16_t yEnd = yStart + HEALTH_BAR_HEIGHT;

        if (currentWidth > 0) {
            drawRectangle(xStart, yStart, xStart + currentWidth, yEnd, color);
        }

        if (lostWidth > 0) {
            drawRectangle(xStart + currentWidth, yStart,xStart + HEALTH_BAR_WIDTH, yEnd, RED);
        }
    }

    void takeDamage(const uint16_t damageValue) {
        if (damageValue >= health_) {
            health_ = 0;
        } else {
            health_ -= damageValue;
        }
    }

    [[nodiscard]] uint16_t getPosX() const { return posX_; }
    [[nodiscard]] uint16_t getPosY() const { return posY_; }
    [[nodiscard]] uint16_t getCameraPosX() const { return cameraPosX_; }
    [[nodiscard]] uint16_t getTilePosX() const { return posX_ / TILE_SQ_SIZE; }
    [[nodiscard]] uint16_t getTilePosY() const { return posY_ / TILE_SQ_SIZE; }
    [[nodiscard]] uint16_t getHealth() const { return health_; }
    void setPosX(const uint16_t pos) { this->posX_ = pos; }
    void setPosY(const uint16_t pos) { this->posY_ = pos; }
    void setHealth(const uint16_t health) { this->health_ = health; }
    void setCameraPosX(const uint16_t pos) { this->cameraPosX_ = pos; }
};

#endif //AION_ZERO_FMW_BASE_ENTITY_HPP