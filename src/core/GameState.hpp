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

struct Player {
  Paddle paddle;
  int score{0};
  int comboHits{0};
  float exMeter{0.0f};
};

struct GameState {
  static constexpr float initialFieldWidth{800.0f};
  static constexpr float fieldHeight{450.0f};
  static constexpr float uiHeight{50.0f};
  static constexpr float sceneHeight{uiHeight + fieldHeight};

  float fieldWidth{initialFieldWidth};
  Ball ball{};
  Player player1{Paddle{32.0f, 185.0f}};
  Player player2{Paddle{756.0f, 185.0f}};

  void SetFieldWidth(float newWidth) {
    if (newWidth <= 0.0f || newWidth == fieldWidth) return;
    const float scale = newWidth / fieldWidth;
    ball.x *= scale;
    fieldWidth = newWidth;
    player2.paddle.x = fieldWidth - 32.0f - player2.paddle.width;
  }
};
