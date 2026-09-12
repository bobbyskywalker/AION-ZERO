#ifndef AION_ZERO_FMW_GAME_ASH_HPP
#define AION_ZERO_FMW_GAME_ASH_HPP

#include <array>
#include <cstdint>

#include "tempMap.hpp"
#include "../../module.hpp"

constexpr uint8_t TILE_SQ_SIZE = 8;
constexpr uint8_t PLAYER_SQ_SIZE = 16;

enum class Game_ASH_State {
    RUNNING,
    PAUSED,
    EXITING,
};

class Game_ASH {
private:
    display::LcdDisplay& display_;
    const std::array<std::array<uint8_t, 16>, 16> gameMap_ = TEMP_MAP;

    void drawTile(const unsigned char* image, uint16_t x, uint16_t y, uint16_t imageWidth, uint16_t imageHeight);
    void processCurrentState();
public:
    explicit Game_ASH(display::LcdDisplay& display);

    void drawMap();

    void drawPlayer();

    ModuleSwitchRequest runGame();
};


#endif //AION_ZERO_FMW_GAME_ASH_HPP