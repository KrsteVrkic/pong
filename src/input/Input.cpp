#include "Input.hpp"

#include <raylib.h>

PlayerInput Input::Read() const {
  PlayerInput input;

  if (IsKeyDown(KEY_W)) input.player1PaddleDirection -= 1.0f;
  if (IsKeyDown(KEY_S)) input.player1PaddleDirection += 1.0f;
  if (IsKeyDown(KEY_UP)) input.player2PaddleDirection -= 1.0f;
  if (IsKeyDown(KEY_DOWN)) input.player2PaddleDirection += 1.0f;
  input.player1Boost = IsKeyDown(KEY_LEFT_SHIFT);
  input.player2Boost = IsKeyDown(KEY_RIGHT_SHIFT);

  return input;
}
