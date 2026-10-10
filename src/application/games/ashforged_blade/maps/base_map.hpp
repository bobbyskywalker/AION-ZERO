#ifndef AION_ZERO_FMW_BASE_MAP_HPP
#define AION_ZERO_FMW_BASE_MAP_HPP

#include <vector>
#include <array>

#include "../../../../display/display.hpp"
#include "../util/draw.hpp"

constexpr uint8_t TILE_SQ_SIZE = 8;
constexpr uint8_t ENTITY_SQ_SIZE = 16;
constexpr uint8_t INITIAL_PLAYER_TILE_X = 7;
constexpr uint8_t INITIAL_PLAYER_TILE_Y = 11;
constexpr uint8_t PLAYER_TO_WALKABLE_TILE_OFFSET = 2;
static constexpr size_t MAP_HEIGHT = 16;
static constexpr size_t MAP_WIDTH = 64;
static constexpr size_t CAMERA_SIZE = 16;

namespace MapDescription {
    enum class TILE_ID {
        TILE_NONE_ID,
        TILE_WALKABLE_ID,
        ENEMY_POS_ID,
        HEALTH_COLLECTIBLE_ID,
        SCORE_COLLECTIBLE_ID
    };
}

class BaseMap {
protected:
    uint8_t scrollX_ = 0;
    uint16_t cameraX_ = 0;

    std::array<std::array<uint8_t, CAMERA_SIZE>, CAMERA_SIZE> camera_{};

public:
    virtual ~BaseMap() = default;

    void updateCamera(uint16_t playerPosX, const std::array<std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT> & map);

    [[nodiscard]] bool isWalkableTileOnPos(
        uint16_t posX,
        uint16_t posY,
        const std::array<std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT> & map
    ) const;

    [[nodiscard]] uint8_t getScrollX() const { return this->scrollX_; }
    void setScrollX(const uint8_t scrollX) { this->scrollX_ = scrollX; }

    [[nodiscard]] uint16_t getCameraX() const { return this->cameraX_; }
    void setCameraX(const uint16_t cameraX) { this->cameraX_ = cameraX; }

    [[nodiscard]] virtual bool isGroundOnPos(uint16_t posY) const;

    [[nodiscard]] virtual const std::array<std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT> &getMap() const = 0;

    static uint16_t getMapWidth() { return MAP_WIDTH; }

    static uint16_t getMapHeight() { return MAP_HEIGHT; }

    [[nodiscard]] virtual const unsigned char* getTileWalkableAsset() const = 0;
    [[nodiscard]] virtual const unsigned char* getBackgroundAsset() const = 0;

    void drawBg(display::LcdDisplay &display, const unsigned char *bg) const;

    void draw(display::LcdDisplay &display, const unsigned char *backgroundAsset, const unsigned char *tileWalkableAsset) const;

    static std::vector<std::pair<uint8_t, uint8_t> > provideTypeCoordinates(
        const std::array<std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT> &map, MapDescription::TILE_ID type
    );

};

#endif //AION_ZERO_FMW_BASE_MAP_HPP
