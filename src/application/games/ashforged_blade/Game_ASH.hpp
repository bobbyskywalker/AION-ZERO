#ifndef AION_ZERO_FMW_GAME_ASH_HPP
#define AION_ZERO_FMW_GAME_ASH_HPP

#include <array>
#include <cstdint>
#include <memory>
#include <queue>

#include "maps/lvl_1.hpp"
#include "maps/lvl_2.hpp"
#include "../../module.hpp"
#include "../../../engine/input.hpp"
#include "collision_scanner.hpp"
#include "collectible/health_collectible.hpp"
#include "collectible/score_collectible.hpp"
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

    std::unique_ptr<std::queue<CollisionScanner::CollisionEvent>> collisionEventQueue_;
    std::unique_ptr<std::queue<InputEngine::ButtonEvent>> eventQueue_;

    display::LcdDisplay& display_;
    std::unique_ptr<BaseMap> gameMap_;

    std::unique_ptr<Player> player_;
    std::vector<std::unique_ptr<Enemy>> enemies_{};
    std::vector<std::variant<HealthCollectible, ScoreCollectible>> collectibles_{};

    uint8_t currentLevel_ = 1;

    void processCurrentState();
    void processGameplayState();
    void processPausedState();
    void processMenuState();

    void drainInputQueue() const;
    void drainCollisionQueue();
    void updatePlayer() const;
    void updateHud();

    void drawMap();
    void drawPlayer() const;
    void drawEnemies() const;
    void drawHud() const;
    void drawCollectibles() const;

    void updateMap() const;

    void spawnCollectibles();
    void updateCollectibles();

    void spawnEnemies();
    void updateEnemies(uint16_t playerPosX) const;
    void removeDeadEnemies();

    void nextLevel();

    static constexpr uint16_t HUD_X = 10;
    static constexpr uint16_t HUD_Y = 10;

public:
    explicit Game_ASH(display::LcdDisplay& display);

    ModuleSwitchRequest runGame();
};


#endif //AION_ZERO_FMW_GAME_ASH_HPP