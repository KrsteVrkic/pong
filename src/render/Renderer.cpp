#include "Renderer.hpp"
#include "Divider.hpp"

#include "../core/GameState.hpp"
#include <raylib.h>
#include <algorithm>

void Renderer::Draw(const GameState& state, bool paused) const {
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

  // HUD: scores, rally hit counts, and each player's EX meter.
  DrawText(TextFormat("P1  %02i   COMBO %i", state.player1.score,
                      state.player1.comboHits),
           static_cast<int>(fieldOffsetX + 18.0f * scale),
           static_cast<int>(sceneOffsetY + 7.0f * scale),
           static_cast<int>(15.0f * scale), WHITE);
  DrawText("EX", static_cast<int>(fieldOffsetX + 160.0f * scale),
           static_cast<int>(sceneOffsetY + 30.0f * scale),
           static_cast<int>(10.0f * scale), accent);
  const float meterWidth = 180.0f * scale;
  const float meterHeight = 8.0f * scale;
  const float meterY = sceneOffsetY + 34.0f * scale;
  const float player1MeterX = fieldOffsetX + 180.0f * scale;
  const float player2MeterX = fieldOffsetX + (state.fieldWidth - 400.0f) * scale;
  DrawRectangleRec(Rectangle{player1MeterX, meterY, meterWidth, meterHeight},
                   Color{55, 57, 72, 255});
  DrawRectangleRec(Rectangle{player1MeterX, meterY,
                             meterWidth * state.player1.exMeter / 100.0f,
                             meterHeight},
                   accent);

  DrawText(TextFormat("P2  %02i   COMBO %i", state.player2.score,
                      state.player2.comboHits),
           static_cast<int>(fieldOffsetX + (state.fieldWidth - 205.0f) * scale),
           static_cast<int>(sceneOffsetY + 7.0f * scale),
           static_cast<int>(15.0f * scale), WHITE);
  DrawText("EX", static_cast<int>(fieldOffsetX + (state.fieldWidth - 420.0f) * scale),
           static_cast<int>(sceneOffsetY + 30.0f * scale),
           static_cast<int>(10.0f * scale), accent);
  DrawRectangleRec(Rectangle{player2MeterX, meterY, meterWidth, meterHeight},
                   Color{55, 57, 72, 255});
  DrawRectangleRec(Rectangle{player2MeterX, meterY,
                             meterWidth * state.player2.exMeter / 100.0f,
                             meterHeight},
                   accent);

  DrawRectangleLinesEx(Rectangle{fieldOffsetX, fieldOffsetY,
                                 fieldWidth, fieldHeight},
                       2.0f * scale, accent);
  divider.Draw(fieldWidth, fieldHeight, dividerGap, fieldOffsetX, fieldOffsetY);

  DrawRectangleRec(
      Rectangle{fieldOffsetX + state.player1.paddle.x * scale,
                fieldOffsetY + state.player1.paddle.y * scale,
                state.player1.paddle.width * scale,
                state.player1.paddle.height * scale},
      WHITE);
  DrawRectangleRec(
      Rectangle{fieldOffsetX + state.player2.paddle.x * scale,
                fieldOffsetY + state.player2.paddle.y * scale,
                state.player2.paddle.width * scale,
                state.player2.paddle.height * scale},
      WHITE);
  DrawCircleV(Vector2{fieldOffsetX + state.ball.x * scale,
                     fieldOffsetY + state.ball.y * scale},
              state.ball.radius * scale, WHITE);

  if (paused) {
    const Color overlay{0, 0, 0, 165};
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), overlay);
    const char* pausedText = "PAUSED";
    const int pausedFontSize = static_cast<int>(42.0f * scale);
    DrawText(pausedText,
             (GetScreenWidth() - MeasureText(pausedText, pausedFontSize)) / 2,
             (GetScreenHeight() - pausedFontSize) / 2,
             pausedFontSize, WHITE);
  }

  EndDrawing();
}
