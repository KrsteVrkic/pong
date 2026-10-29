#pragma once

struct GameState;

class Renderer {
 public:
  void Draw(const GameState& state) const;
};
