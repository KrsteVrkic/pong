#pragma once

#include "../input/Input.hpp"

struct GameState;

class GameLogic {
 public:
  void Update(GameState& state, const PlayerInput& input, float deltaTime) const;
};
