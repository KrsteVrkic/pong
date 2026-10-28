#include "Game.h"
#include <raylib.h>

void Game::Run() {
  int screenWidth = 800;
  int screenHeight = 450;
  
  InitWindow(screenWidth, screenHeight, "pong");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawCircle(screenWidth / 4, screenHeight / 4, 10, WHITE);
    EndDrawing();
  }

  CloseWindow();
}

