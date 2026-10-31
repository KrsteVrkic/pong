#pragma once
#include "Divider.hpp"
struct GameState;

class Renderer {
 public:
  void Draw(const GameState& state) const;

 private:
  Divider divider;
};
