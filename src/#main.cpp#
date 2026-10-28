#include <raylib.h>

int main() {
  constexpr int screenWidth = 800;
  constexpr int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Pong");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawCircle(screenWidth / 2, screenHeight / 2, 10, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

