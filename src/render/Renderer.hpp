#pragma once
#include "Divider.hpp"
struct GameState;

class Renderer {
 public:
  void Draw(const GameState& state, bool paused = false) const;

 private:
  Divider divider;
};
