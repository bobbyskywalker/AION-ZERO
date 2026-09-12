#ifndef AION_ZERO_FMW_GAME_ASH_HPP
#define AION_ZERO_FMW_GAME_ASH_HPP

#include <array>
#include <cstdint>

#include "tempMap.hpp"
#include "../../module.hpp"

extern "C" {
#include "GUI_Paint.h"
#include "LCD_1in44.h"
#include "DEV_Config.h"
}

auto constexpr TILE_SQ_SIZE = 8;

enum class Game_ASH_State {
    RUNNING,
    PAUSED,
    EXITING,
};

class Game_ASH {
private:
    const std::array<std::array<uint8_t, 16>, 16> gameMap_ = TEMP_MAP;

    void drawTile(const unsigned char* image, uint16_t x, uint16_t y, uint16_t imageWidth, uint16_t imageHeight);
    void processCurrentState();
public:
    Game_ASH() = default;

    void drawMap();
    ModuleSwitchRequest runGame();
};


#endif //AION_ZERO_FMW_GAME_ASH_HPP