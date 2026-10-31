#include "Renderer.hpp"
#include "Divider.hpp"

#include "../core/GameState.hpp"
#include <raylib.h>
#include <algorithm>

void Renderer::Draw(const GameState& state) const {
  BeginDrawing();
  ClearBackground(Color{24, 24, 24, 255});

  const float scale = std::min(
      static_cast<float>(GetScreenWidth()) / GameState::fieldWidth,
      static_cast<float>(GetScreenHeight()) / GameState::fieldHeight);
  const float fieldWidth = GameState::fieldWidth * scale;
  const float fieldHeight = GameState::fieldHeight * scale;
  const float offsetX = (GetScreenWidth() - fieldWidth) / 2.0f;
  const float offsetY = (GetScreenHeight() - fieldHeight) / 2.0f;
  const int dividerGap = 15;

  divider.Draw(fieldWidth, fieldHeight, dividerGap, offsetX, offsetY);

  DrawRectangleRec(
      Rectangle{offsetX + state.leftPaddle.x * scale,
                offsetY + state.leftPaddle.y * scale,
                state.leftPaddle.width * scale,
                state.leftPaddle.height * scale},
      WHITE);
  DrawRectangleRec(
      Rectangle{offsetX + state.rightPaddle.x * scale,
                offsetY + state.rightPaddle.y * scale,
                state.rightPaddle.width * scale,
                state.rightPaddle.height * scale},
      WHITE);
  DrawCircleV(Vector2{offsetX + state.ball.x * scale,
                     offsetY + state.ball.y * scale},
              state.ball.radius * scale, WHITE);

  EndDrawing();
}
