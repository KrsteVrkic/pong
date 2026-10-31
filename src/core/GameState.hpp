#pragma once

struct Ball {
  float x{400.0f};
  float y{225.0f};
  float radius{10.0f};
  float speedX{260.0f};
  float speedY{180.0f};
};

struct Paddle {
  float x;
  float y;
  float width{12.0f};
  float height{80.0f};
  float speed{320.0f};
};

struct GameState {
  static constexpr float fieldWidth{800.0f};
  static constexpr float fieldHeight{450.0f};

  Ball ball{};
  Paddle leftPaddle{32.0f, 185.0f};
  Paddle rightPaddle{756.0f, 185.0f};
};
