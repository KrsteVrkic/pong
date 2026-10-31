#include "Game.hpp"

#include "../core/GameState.hpp"
#include "../gameplay/GameLogic.hpp"
#include "../input/Input.hpp"
#include "../render/Renderer.hpp"

#include <raylib.h>

void Game::Run() {
  InitWindow(800, 450, "pong");
  SetTargetFPS(60);

  GameState state;
  Input input;
  GameLogic gameLogic;
  Renderer renderer;

  while (!WindowShouldClose()) {
    const PlayerInput playerInput = input.Read();
    gameLogic.Update(state, playerInput, GetFrameTime());
    renderer.Draw(state);
  }

  CloseWindow();
}
