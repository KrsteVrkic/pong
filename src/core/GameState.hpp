#pragma once

struct Ball {
  static constexpr float baseSpeedX{780.0f};
  static constexpr float baseSpeedY{540.0f};

  float x{400.0f};
  float y{225.0f};
  float radius{10.0f};
  float speedX{baseSpeedX};
  float speedY{baseSpeedY};
};

struct Paddle {
  float x;
  float y;
  float width{12.0f};
  float height{80.0f};
  float speed{320.0f};
};

struct GameState {
  static constexpr float initialFieldWidth{800.0f};
  static constexpr float fieldHeight{450.0f};
  static constexpr float uiHeight{50.0f};
  static constexpr float sceneHeight{uiHeight + fieldHeight};

  float fieldWidth{initialFieldWidth};
  Ball ball{};
  Paddle leftPaddle{32.0f, 185.0f};
  Paddle rightPaddle{756.0f, 185.0f};

  void SetFieldWidth(float newWidth) {
    if (newWidth <= 0.0f || newWidth == fieldWidth) return;
    const float scale = newWidth / fieldWidth;
    ball.x *= scale;
    fieldWidth = newWidth;
    rightPaddle.x = fieldWidth - 32.0f - rightPaddle.width;
  }
};
