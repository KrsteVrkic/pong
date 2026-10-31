#include "Renderer.hpp"

#include "../core/GameState.hpp"
#include <raylib.h>

void Renderer::Draw(const GameState& state) const {
  BeginDrawing();
  ClearBackground(Color{24, 24, 24, 255});

  const float fieldWidth = static_cast<float>(GetScreenWidth());
  const float fieldHeight = static_cast<float>(GetScreenHeight());
  const float dividerWidth = fieldWidth * 0.005f;
  constexpr int dashCount = 15;
  constexpr float gapToDashRatio = 0.5f;
  const float dashHeight = fieldHeight /
      (dashCount + (dashCount - 1) * gapToDashRatio);
  const float dashStep = dashHeight * (1.0f + gapToDashRatio);

  for (int i = 0; i < dashCount; ++i) {
    const float y = i * dashStep;
    DrawRectangleRec(
        Rectangle{fieldWidth / 2.0f - dividerWidth / 2.0f, y,
                  dividerWidth, dashHeight},
        WHITE);
  }

  DrawRectangleRounded(Rectangle{state.leftPaddle.x, state.leftPaddle.y,
                                 state.leftPaddle.width, state.leftPaddle.height},
                       0.45f, 8, Color{WHITE});
  DrawRectangleRounded(Rectangle{state.rightPaddle.x, state.rightPaddle.y,
                                 state.rightPaddle.width, state.rightPaddle.height},
                       0.45f, 8, Color{WHITE});
  DrawCircle(static_cast<int>(state.ball.x), static_cast<int>(state.ball.y),
             state.ball.radius, Color{WHITE});
  EndDrawing();
}
