#include "enemy_animator.hpp"
#include "enemy.hpp"
#include "enemy_state.hpp"

EnemyAnimator::EnemyAnimator(Enemy & e) : EntityAnimator(), enemy_(e) {}

void EnemyAnimator::drawNextFrameForCurrentState(const EnemyState state) {
    const uint16_t screenX = this->enemy_.getPosX() - this->enemy_.getCameraPosX();

    if (state == EnemyState::FOLLOWING) {
        drawSprite(FOLLOWING_FRAMES[currentFrame_], screenX, enemy_.getPosY(), ENTITY_SQ_SIZE, ENTITY_SQ_SIZE);
    } else if (state == EnemyState::ATTACKING) {
        this->updateFrameAndTimer(ATTACK_FRAMES, ATTACK_FPS);
        drawSprite(
            ATTACK_FRAMES[currentFrame_], screenX, enemy_.getPosY(), ENTITY_SQ_SIZE, ENTITY_SQ_SIZE
        );
        if (currentFrame_ == std::size(ATTACK_FRAMES) - 1) {
            this->enemy_.animationEndedForCurrentStateEvent(EnemyState::ATTACKING);
        }
    }
}
