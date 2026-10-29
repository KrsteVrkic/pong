#include "Renderer.hpp"

#include "../core/GameState.hpp"
#include <raylib.h>

void Renderer::Draw(const GameState& state) const {
  BeginDrawing();
  ClearBackground(BLACK);
  DrawCircle(static_cast<int>(state.ball.x), static_cast<int>(state.ball.y),
             state.ball.radius, WHITE);
  EndDrawing();
}
