#pragma once

struct Ball {
    float x;
    float y;
    float radius;
};

struct GameState {
    Ball ball{400.0f, 225.0f, 10.0f};
};
