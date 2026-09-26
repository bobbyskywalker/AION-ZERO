#ifndef AION_ZERO_FMW_BASE_MAP_HPP
#define AION_ZERO_FMW_BASE_MAP_HPP
#include <vector>

constexpr uint8_t TILE_SQ_SIZE = 8;
constexpr uint8_t ENTITY_SQ_SIZE = 16;
constexpr uint8_t INITIAL_PLAYER_TILE_X = 7;
constexpr uint8_t INITIAL_PLAYER_TILE_Y = 11;
constexpr uint8_t PLAYER_TO_WALKABLE_TILE_OFFSET = 2;

namespace MapDescription {
    constexpr uint8_t TILE_WALKABLE_ID = 1;
    constexpr uint8_t ENEMY_POS_ID = 2;
}

class BaseMap {
public:
    static constexpr size_t MAP_HEIGHT = 16;
    static constexpr size_t MAP_WIDTH = 64;
    static constexpr size_t CAMERA_SIZE = 16;

    virtual ~BaseMap() = default;
    virtual void draw(display::LcdDisplay& display) = 0;
    virtual void drawBg(display::LcdDisplay& display) = 0;
    virtual void updateCamera(uint16_t playerPos) = 0;
    virtual std::vector<std::pair<uint8_t, uint8_t> > provideEnemyCoordinates() = 0;
    [[nodiscard]] virtual uint16_t getCameraX() const = 0;
    [[nodiscard]] virtual uint16_t getMapWidth() const = 0;
    [[nodiscard]] virtual uint16_t getMapHeight() const = 0;
    [[nodiscard]] virtual bool isGroundOnPos(uint16_t posY) const = 0;
    [[nodiscard]] virtual bool isWalkableTileOnPos(uint16_t posX, uint16_t posY) const = 0;
};

#endif //AION_ZERO_FMW_BASE_MAP_HPP