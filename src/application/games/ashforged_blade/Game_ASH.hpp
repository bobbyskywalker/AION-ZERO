#ifndef AION_ZERO_FMW_GAME_ASH_HPP
#define AION_ZERO_FMW_GAME_ASH_HPP

#include <array>
#include <cstdint>
#include <memory>
#include <queue>

#include "maps/lvl_1.hpp"
#include "../../module.hpp"
#include "../../../engine/input.hpp"
#include "entity/enemy/enemy.hpp"
#include "entity/player/player.hpp"

static uint64_t constexpr FPS =  33'000;

enum class Game_ASH_State {
    MENU,
    GAMEPLAY,
    PAUSED
};

namespace ASH_GAMEPLAY_BUTTONS {
    constexpr uint8_t BUTTON_LEFT = 0;
    constexpr uint8_t BUTTON_RIGHT = 1;
    constexpr uint8_t BUTTON_JUMP = 2;
    constexpr uint8_t BUTTON_ATTACK = 3;
}

namespace ASH_MENU_BUTTONS {
    constexpr uint8_t BUTTON_UP = 0;
    constexpr uint8_t BUTTON_DOWN = 1;
    constexpr uint8_t BUTTON_ENTER = 2;
    constexpr uint8_t BUTTON_BACK = 3;
}


class Game_ASH {
private:
    Game_ASH_State currentState_;
    std::unique_ptr<std::queue<InputEngine::ButtonEvent>> eventQueue_;

    display::LcdDisplay& display_;
    std::unique_ptr<BaseMap> gameMap_;

    std::unique_ptr<Player> player_;
    std::vector<Enemy> enemies_{};

    void processCurrentState();
    void processGameplayState();
    void processPausedState();
    void processMenuState();

    void drainInputQueue() const;
    void updatePlayer() const;

    void drawMap();
    void drawPlayer() const;
    void drawEnemies();

    void updateMap() const;

    void spawnEnemies();
    void updateEnemies(uint16_t playerPosX);

public:
    explicit Game_ASH(display::LcdDisplay& display);

    ModuleSwitchRequest runGame();
};


#endif //AION_ZERO_FMW_GAME_ASH_HPP