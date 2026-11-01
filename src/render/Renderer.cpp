#include "Renderer.hpp"
#include "Divider.hpp"

#include "../core/GameState.hpp"
#include <raylib.h>
#include <algorithm>

void Renderer::Draw(const GameState& state) const {
  BeginDrawing();
  ClearBackground(Color{24, 24, 24, 255});

  const float scale = std::min(
      static_cast<float>(GetScreenWidth()) / state.fieldWidth,
      static_cast<float>(GetScreenHeight()) / GameState::sceneHeight);
  const float fieldWidth = state.fieldWidth * scale;
  const float fieldHeight = GameState::fieldHeight * scale;
  const float sceneOffsetX = (GetScreenWidth() - state.fieldWidth * scale) / 2.0f;
  const float sceneOffsetY = (GetScreenHeight() - GameState::sceneHeight * scale) / 2.0f;
  const float fieldOffsetX = sceneOffsetX;
  const float fieldOffsetY = sceneOffsetY + GameState::uiHeight * scale;
  const int dividerGap = 15;
  const Color accent{105, 114, 240, 255};

  DrawRectangleLinesEx(Rectangle{fieldOffsetX, fieldOffsetY,
                                 fieldWidth, fieldHeight},
                       2.0f * scale, accent);
  divider.Draw(fieldWidth, fieldHeight, dividerGap, fieldOffsetX, fieldOffsetY);

  DrawRectangleRec(
      Rectangle{fieldOffsetX + state.leftPaddle.x * scale,
                fieldOffsetY + state.leftPaddle.y * scale,
                state.leftPaddle.width * scale,
                state.leftPaddle.height * scale},
      WHITE);
  DrawRectangleRec(
      Rectangle{fieldOffsetX + state.rightPaddle.x * scale,
                fieldOffsetY + state.rightPaddle.y * scale,
                state.rightPaddle.width * scale,
                state.rightPaddle.height * scale},
      WHITE);
  DrawCircleV(Vector2{fieldOffsetX + state.ball.x * scale,
                     fieldOffsetY + state.ball.y * scale},
              state.ball.radius * scale, WHITE);

  EndDrawing();
}
