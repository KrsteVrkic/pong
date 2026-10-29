#include "Game.hpp"
#include "../core/GameState.hpp"
#include <raylib.h>

void Game::Run() {
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "pong");
    SetTargetFPS(60);

       GameState state;

    while (!WindowShouldClose()) {
        // TODO: Update game logic / physics here later

        BeginDrawing();
        ClearBackground(BLACK);
        
        // Draw using data from core state instead of hardcoded numbers
        DrawCircle(state.ball.x, state.ball.y, state.ball.radius, WHITE);
        
        EndDrawing();
    }

    CloseWindow();
}
