#include "Renderer.hpp"
#include "Divider.hpp"

#include "../core/GameState.hpp"
#include <raylib.h>

void Renderer::Draw(const GameState& state) const {
  BeginDrawing();
  ClearBackground(Color{24, 24, 24, 255});

  const float fieldWidth = static_cast<float>(GetScreenWidth());
  const float fieldHeight = static_cast<float>(GetScreenHeight());
  const int dividerGap = 15;
  
  divider.Draw(fieldWidth, fieldHeight, dividerGap);

  EndDrawing();
}
