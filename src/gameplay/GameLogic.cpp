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
}  // namespace

void GameLogic::Update(GameState& state, const PlayerInput& input,
                       float deltaTime) const {
  UpdatePaddle(state.leftPaddle, input.leftPaddleDirection, deltaTime);
  UpdatePaddle(state.rightPaddle, input.rightPaddleDirection, deltaTime);

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

  if (ball.speedX < 0.0f && Overlaps(ball, state.leftPaddle)) {
    ball.x = state.leftPaddle.x + state.leftPaddle.width + ball.radius;
    ball.speedX = std::abs(ball.speedX);
    ball.speedY +=
        ((ball.y - (state.leftPaddle.y + state.leftPaddle.height / 2.0f)) /
         (state.leftPaddle.height / 2.0f)) *
        70.0f;
  } else if (ball.speedX > 0.0f && Overlaps(ball, state.rightPaddle)) {
    ball.x = state.rightPaddle.x - ball.radius;
    ball.speedX = -std::abs(ball.speedX);
    ball.speedY +=
        ((ball.y - (state.rightPaddle.y + state.rightPaddle.height / 2.0f)) /
         (state.rightPaddle.height / 2.0f)) *
        70.0f;
  }

  // Restart from the center when the ball leaves either side of the field.
  if (ball.x + ball.radius < 0.0f ||
      ball.x - ball.radius > GameState::fieldWidth) {
    ball.x = GameState::fieldWidth / 2.0f;
    ball.y = GameState::fieldHeight / 2.0f;
    ball.speedX = ball.speedX < 0.0f ? 260.0f : -260.0f;
    ball.speedY = 180.0f;
  }
}
