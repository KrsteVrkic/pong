#include "../ui/MainMenu.hpp"
#include "../core/GameState.hpp"

#include <raylib.h>
#include <algorithm>

bool MainMenu::Update() const {
  return IsKeyPressed(KEY_ENTER);
}

void MainMenu::Draw() {
  BeginDrawing();
  ClearBackground(Color{24, 24, 24, 255});

  const float scale = std::min(
      static_cast<float>(GetScreenWidth()) / GameState::initialFieldWidth,
      static_cast<float>(GetScreenHeight()) / GameState::sceneHeight);
  const float offsetX =
      (GetScreenWidth() - GameState::initialFieldWidth * scale) / 2.0f;
  const float offsetY =
      (GetScreenHeight() - GameState::sceneHeight * scale) / 2.0f;

  constexpr int titleFontSize = 50;
  constexpr int promptFontSize = 24;
  const char* title = "PONG";
  const char* prompt = "Press Enter to Play";
  const int scaledTitleFontSize = static_cast<int>(titleFontSize * scale);
  const int scaledPromptFontSize = static_cast<int>(promptFontSize * scale);

  const int titleWidth = MeasureText(title, scaledTitleFontSize);
  const int promptWidth = MeasureText(prompt, scaledPromptFontSize);
  DrawText(title,
           static_cast<int>(offsetX +
                            (GameState::initialFieldWidth * scale - titleWidth) /
                                2.0f),
           static_cast<int>(offsetY + 150.0f * scale), scaledTitleFontSize,
           WHITE);
  DrawText(prompt,
           static_cast<int>(offsetX +
                            (GameState::initialFieldWidth * scale - promptWidth) /
                                2.0f),
           static_cast<int>(offsetY + 240.0f * scale), scaledPromptFontSize,
           WHITE);

  EndDrawing();
}
