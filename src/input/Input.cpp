#include "Input.hpp"

#include <raylib.h>

PlayerInput Input::Read() const {
  PlayerInput input;

  if (IsKeyDown(KEY_W)) input.leftPaddleDirection -= 1.0f;
  if (IsKeyDown(KEY_S)) input.leftPaddleDirection += 1.0f;
  if (IsKeyDown(KEY_UP)) input.rightPaddleDirection -= 1.0f;
  if (IsKeyDown(KEY_DOWN)) input.rightPaddleDirection += 1.0f;

  return input;
}
