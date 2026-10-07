#ifndef AION_ZERO_FMW_BASE_COLLECTIBLE_HPP
#define AION_ZERO_FMW_BASE_COLLECTIBLE_HPP

#include <cstdint>

class BaseCollectible {
protected:
    uint16_t posX_;
    uint16_t posY_;
    uint16_t cameraPosX_{};

public:
    explicit BaseCollectible(const uint16_t initialX, const uint16_t initialY) : posX_(initialX), posY_(initialY) {}
    virtual ~BaseCollectible() = default;

    virtual void draw() const = 0;

    [[nodiscard]] uint16_t getPosX() const { return posX_; }
    [[nodiscard]] uint16_t getPosY() const { return posY_; }
    [[nodiscard]] uint16_t getCameraPosX() const { return cameraPosX_; }
    void setPosX(const uint16_t pos) { this->posX_ = pos; }
    void setPosY(const uint16_t pos) { this->posY_ = pos; }
    void setCameraPosX(const uint16_t pos) { this->cameraPosX_ = pos; }
};

#endif //AION_ZERO_FMW_BASE_COLLECTIBLE_HPP