#pragma once

struct PlayerInput {
  float player1PaddleDirection{0.0f};
  float player2PaddleDirection{0.0f};
  bool player1Boost{false};
  bool player2Boost{false};
};

class Input {
 public:
  PlayerInput Read() const;
};
