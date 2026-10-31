#pragma once

struct PlayerInput {
  float leftPaddleDirection{0.0f};
  float rightPaddleDirection{0.0f};
};

class Input {
 public:
  PlayerInput Read() const;
};
