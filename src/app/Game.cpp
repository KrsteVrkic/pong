#include "Game.hpp"
#include "../core/GameState.hpp"
#include "../render/Renderer.hpp"
#include <raylib.h>

void Game::Run() {
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "pong");
    SetTargetFPS(60);

    GameState state;
    Renderer renderer;

    while (!WindowShouldClose()) {
        // TODO: Update game logic / physics here later
        renderer.Draw(state);
    }

    CloseWindow();
}
