#include "GameLogic.hpp"

#include "../core/GameState.hpp"

#include <algorithm>
#include <cmath>

namespace {
void UpdatePaddle(Paddle& paddle, float direction, float deltaTime) {
  paddle.y += direction * paddle.speed * deltaTime;
  paddle.y = std::clamp(paddle.y, 0.0f,
                        GameState::fieldHeight - paddle.height);
}

bool Overlaps(const Ball& ball, const Paddle& paddle) {
  return ball.x + ball.radius >= paddle.x &&
         ball.x - ball.radius <= paddle.x + paddle.width &&
         ball.y + ball.radius >= paddle.y &&
         ball.y - ball.radius <= paddle.y + paddle.height;
}

void MovePlayer(Player& player, float direction, bool boost, float deltaTime) {
  constexpr float boostMultiplier = 1.8f;
  constexpr float exDrainPerSecond = 35.0f;
  const bool boosted = boost && player.exMeter > 0.0f;
  const float speedMultiplier = boosted ? boostMultiplier : 1.0f;
  UpdatePaddle(player.paddle, direction, deltaTime * speedMultiplier);
  if (boosted) {
    player.exMeter = std::max(0.0f, player.exMeter - exDrainPerSecond * deltaTime);
  }
}

void RegisterHit(Player& hitter) {
  ++hitter.comboHits;
  hitter.exMeter = std::min(100.0f, hitter.exMeter + 12.0f);
}
}  // namespace

void GameLogic::Update(GameState& state, const PlayerInput& input,
                       float deltaTime) const {
  MovePlayer(state.player1, input.player1PaddleDirection,
             input.player1Boost, deltaTime);
  MovePlayer(state.player2, input.player2PaddleDirection,
             input.player2Boost, deltaTime);

  Ball& ball = state.ball;
  ball.x += ball.speedX * deltaTime;
  ball.y += ball.speedY * deltaTime;

  if (ball.y - ball.radius <= 0.0f) {
    ball.y = ball.radius;
    ball.speedY = std::abs(ball.speedY);
  } else if (ball.y + ball.radius >= GameState::fieldHeight) {
    ball.y = GameState::fieldHeight - ball.radius;
    ball.speedY = -std::abs(ball.speedY);
  }

  if (ball.speedX < 0.0f && Overlaps(ball, state.player1.paddle)) {
    const Paddle& paddle = state.player1.paddle;
    ball.x = paddle.x + paddle.width + ball.radius;
    ball.speedX = std::abs(ball.speedX);
    ball.speedY +=
        ((ball.y - (paddle.y + paddle.height / 2.0f)) /
         (paddle.height / 2.0f)) *
        210.0f;
    RegisterHit(state.player1);
  } else if (ball.speedX > 0.0f && Overlaps(ball, state.player2.paddle)) {
    const Paddle& paddle = state.player2.paddle;
    ball.x = paddle.x - ball.radius;
    ball.speedX = -std::abs(ball.speedX);
    ball.speedY +=
        ((ball.y - (paddle.y + paddle.height / 2.0f)) /
         (paddle.height / 2.0f)) *
        210.0f;
    RegisterHit(state.player2);
  }

  // Restart from the center when the ball leaves either side of the field.
  if (ball.x + ball.radius < 0.0f ||
      ball.x - ball.radius > state.fieldWidth) {
    const bool player1Scored = ball.x - ball.radius > state.fieldWidth;
    if (player1Scored) {
      ++state.player1.score;
    } else {
      ++state.player2.score;
    }
    state.player1.comboHits = 0;
    state.player2.comboHits = 0;
    ball.x = state.fieldWidth / 2.0f;
    ball.y = GameState::fieldHeight / 2.0f;
    ball.speedX = player1Scored ? Ball::baseSpeedX : -Ball::baseSpeedX;
    ball.speedY = Ball::baseSpeedY;
  }
}
