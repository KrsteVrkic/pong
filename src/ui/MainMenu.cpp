#include "../ui/MainMenu.hpp"
#include "../core/GameState.hpp"

#include <raylib.h>
#include <algorithm>

namespace {
constexpr int optionCount = 3;
constexpr Color accent{105, 114, 240, 255};

float MenuScale() {
  return std::min(
      static_cast<float>(GetScreenWidth()) / GameState::initialFieldWidth,
      static_cast<float>(GetScreenHeight()) / GameState::sceneHeight);
}

float MenuOffsetX(float scale) {
  return (GetScreenWidth() - GameState::initialFieldWidth * scale) / 2.0f;
}

float MenuOffsetY(float scale) {
  return (GetScreenHeight() - GameState::sceneHeight * scale) / 2.0f;
}
}  // namespace

MainMenuAction MainMenu::Update() {
  if (IsKeyPressed(KEY_UP)) {
    selectedOption = (selectedOption + optionCount - 1) % optionCount;
  }
  if (IsKeyPressed(KEY_DOWN)) {
    selectedOption = (selectedOption + 1) % optionCount;
  }

  if (!IsKeyPressed(KEY_ENTER)) return MainMenuAction::None;

  switch (selectedOption) {
    case 0: return MainMenuAction::Play;
    case 1: return MainMenuAction::Settings;
    case 2: return MainMenuAction::Quit;
    default: return MainMenuAction::None;
  }
}

void MainMenu::Draw() const {
  BeginDrawing();
  ClearBackground(Color{24, 24, 24, 255});

  const float scale = MenuScale();
  const float offsetX = MenuOffsetX(scale);
  const float offsetY = MenuOffsetY(scale);
  const int titleSize = static_cast<int>(48.0f * scale);
  const int optionSize = static_cast<int>(26.0f * scale);
  const char* title = "PONG";
  const char* options[optionCount] = {"Play", "Settings", "Quit"};
  const int titleWidth = MeasureText(title, titleSize);

  DrawText(title,
           static_cast<int>(offsetX +
                            (GameState::initialFieldWidth * scale - titleWidth) /
                                2.0f),
           static_cast<int>(offsetY + 115.0f * scale), titleSize, WHITE);

  for (int i = 0; i < optionCount; ++i) {
    const int textWidth = MeasureText(options[i], optionSize);
    const int x = static_cast<int>(offsetX +
                                   (GameState::initialFieldWidth * scale -
                                    textWidth) /
                                       2.0f);
    const int y = static_cast<int>(offsetY + (220.0f + i * 48.0f) * scale);
    const Color color = i == selectedOption ? accent : WHITE;
    if (i == selectedOption) {
      DrawText(">", x - static_cast<int>(24.0f * scale), y, optionSize,
               accent);
    }
    DrawText(options[i], x, y, optionSize, color);
  }

  EndDrawing();
}

void MainMenu::DrawSettings() const {
  BeginDrawing();
  ClearBackground(Color{24, 24, 24, 255});

  const float scale = MenuScale();
  const float offsetX = MenuOffsetX(scale);
  const float offsetY = MenuOffsetY(scale);
  const char* message = "Settings are not available yet";
  const int fontSize = static_cast<int>(24.0f * scale);
  const int messageWidth = MeasureText(message, fontSize);

  DrawText("SETTINGS", static_cast<int>(offsetX + 300.0f * scale),
           static_cast<int>(offsetY + 170.0f * scale),
           static_cast<int>(36.0f * scale), WHITE);
  DrawText(message,
           static_cast<int>(offsetX +
                            (GameState::initialFieldWidth * scale - messageWidth) /
                                2.0f),
           static_cast<int>(offsetY + 250.0f * scale), fontSize, WHITE);
  DrawText("Press Esc to return",
           static_cast<int>(offsetX + 305.0f * scale),
           static_cast<int>(offsetY + 320.0f * scale),
           static_cast<int>(18.0f * scale), Color{160, 160, 170, 255});

  EndDrawing();
}
