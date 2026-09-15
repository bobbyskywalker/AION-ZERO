#ifndef AION_ZERO_FMW_GAME_ASH_HPP
#define AION_ZERO_FMW_GAME_ASH_HPP

#include <array>
#include <cstdint>
#include <memory>

#include "maps/lvl_1.hpp"
#include "../../module.hpp"
#include "util/draw.hpp"
#include "entity/player.hpp"

constexpr uint8_t PLAYER_SQ_SIZE = 16;

enum class Game_ASH_State {
    RUNNING,
    PAUSED,
    EXITING,
};

class Game_ASH {
private:
    display::LcdDisplay& display_;
    std::unique_ptr<BaseMap> gameMap_;

    std::unique_ptr<Player> player_;

    void processCurrentState();
public:
    explicit Game_ASH(display::LcdDisplay& display);

    void drawMap();

    void drawPlayer() const;

    ModuleSwitchRequest runGame();
};


#endif //AION_ZERO_FMW_GAME_ASH_HPP