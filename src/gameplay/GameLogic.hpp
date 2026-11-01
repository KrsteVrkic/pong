#pragma once

#include "../input/Input.hpp"

#include <random>

struct GameState;

struct GameEvents {
  bool paddleHit{false};
  bool wallHit{false};
  bool pointScored{false};
};

class GameLogic {
 public:
  GameEvents Update(GameState& state, const PlayerInput& input, float deltaTime);

 private:
  std::mt19937 randomGenerator{std::random_device{}()};
};
