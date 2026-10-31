#include "Game.hpp"
#include "../core/GameState.hpp"
#include "../render/Renderer.hpp"
#include <raylib.h>
#include <algorithm>

namespace {
void UpdatePaddle(Paddle& paddle, float direction, float deltaTime) {
    paddle.y += direction * paddle.speed * deltaTime;
    paddle.y = std::clamp(paddle.y, 0.0f, GameState::fieldHeight - paddle.height);
}

bool Overlaps(const Ball& ball, const Paddle& paddle) {
    return ball.x + ball.radius >= paddle.x &&
           ball.x - ball.radius <= paddle.x + paddle.width &&
           ball.y + ball.radius >= paddle.y &&
           ball.y - ball.radius <= paddle.y + paddle.height;
}

void UpdateGame(GameState& state, float deltaTime) {
    float leftDirection = 0.0f;
    if (IsKeyDown(KEY_W)) leftDirection -= 1.0f;
    if (IsKeyDown(KEY_S)) leftDirection += 1.0f;
    UpdatePaddle(state.leftPaddle, leftDirection, deltaTime);

    float rightDirection = 0.0f;
    if (IsKeyDown(KEY_UP)) rightDirection -= 1.0f;
    if (IsKeyDown(KEY_DOWN)) rightDirection += 1.0f;
    UpdatePaddle(state.rightPaddle, rightDirection, deltaTime);

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
        ball.speedY += ((ball.y - (state.leftPaddle.y + state.leftPaddle.height / 2.0f)) /
                        (state.leftPaddle.height / 2.0f)) * 70.0f;
    } else if (ball.speedX > 0.0f && Overlaps(ball, state.rightPaddle)) {
        ball.x = state.rightPaddle.x - ball.radius;
        ball.speedX = -std::abs(ball.speedX);
        ball.speedY += ((ball.y - (state.rightPaddle.y + state.rightPaddle.height / 2.0f)) /
                        (state.rightPaddle.height / 2.0f)) * 70.0f;
    }

    // Restart from the center when the ball leaves either side of the field.
    if (ball.x + ball.radius < 0.0f || ball.x - ball.radius > GameState::fieldWidth) {
        ball.x = GameState::fieldWidth / 2.0f;
        ball.y = GameState::fieldHeight / 2.0f;
        ball.speedX = ball.speedX < 0.0f ? 260.0f : -260.0f;
        ball.speedY = 180.0f;
    }
}
}  // namespace

void Game::Run() {
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "pong");
    SetTargetFPS(60);

    GameState state;
    Renderer renderer;

    while (!WindowShouldClose()) {
        UpdateGame(state, GetFrameTime());
        renderer.Draw(state);
    }

    CloseWindow();
}
