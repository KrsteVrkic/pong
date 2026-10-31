#pragma once

struct Ball {
    float x;
    float y;
    float radius;
};

struct Paddle {
    float x;
    float y;
    float width;
    float height;
};

struct GameState {
    Ball ball{400.0f, 225.0f, 10.0f};
    Paddle leftPaddle{32.0f, 185.0f, 12.0f, 80.0f};
    Paddle rightPaddle{756.0f, 185.0f, 12.0f, 80.0f};
    float fieldWidth{800.0f};
    float fieldHeight{450.0f};
};
