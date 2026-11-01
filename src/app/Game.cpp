#include "Game.hpp"

#include "../core/GameState.hpp"
#include "../gameplay/GameLogic.hpp"
#include "../input/Input.hpp"
#include "../render/Renderer.hpp"

#include <raylib.h>
#include <algorithm>

void Game::Run() {
  InitWindow(static_cast<int>(GameState::initialFieldWidth),
             static_cast<int>(GameState::sceneHeight), "pong");
  SetTargetFPS(60);

  GameState state;
  Input input;
  GameLogic gameLogic;
  Renderer renderer;

  while (!WindowShouldClose()) {
    const float scale = std::min(
        static_cast<float>(GetScreenWidth()) / GameState::initialFieldWidth,
        static_cast<float>(GetScreenHeight()) / GameState::sceneHeight);
    state.SetFieldWidth(static_cast<float>(GetScreenWidth()) / scale);

    const PlayerInput playerInput = input.Read();
    gameLogic.Update(state, playerInput, GetFrameTime());
    renderer.Draw(state);
  }

  CloseWindow();
}
