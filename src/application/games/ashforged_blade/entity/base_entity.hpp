#ifndef AION_ZERO_FMW_BASE_ENTITY_HPP
#define AION_ZERO_FMW_BASE_ENTITY_HPP

#include <cstdint>
#include "../maps/lvl_1.hpp"

class BaseEntity {
protected:
    BaseMap & map_;

    uint16_t posX_;
    uint16_t posY_;
    uint16_t cameraPosX_{};

public:
    explicit BaseEntity(
        const uint16_t initialX,
        const uint16_t initialY,
        BaseMap & map
    ) : map_(map), posX_(initialX), posY_(initialY) {}
    virtual ~BaseEntity() = default;

    virtual void draw() = 0;

    [[nodiscard]] uint16_t getPosX() const { return posX_; }
    [[nodiscard]] uint16_t getPosY() const { return posY_; }
    [[nodiscard]] uint16_t getCameraPosX() const { return cameraPosX_; }
    [[nodiscard]] uint16_t getTilePosX() const { return posX_ / TILE_SQ_SIZE; }
    [[nodiscard]] uint16_t getTilePosY() const { return posY_ / TILE_SQ_SIZE; }
    void setPosX(const uint16_t pos) { this->posX_ = pos; }
    void setPosY(const uint16_t pos) { this->posY_ = pos; }
    void setCameraPosX(const uint16_t pos) { this->cameraPosX_ = pos; }
};

#endif //AION_ZERO_FMW_BASE_ENTITY_HPP