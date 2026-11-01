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
  ChangeDirectory(GetApplicationDirectory());
  InitAudioDevice();
  SetTargetFPS(60);

  Sound paddleHit = LoadSound("assets/audio/paddle_hit.wav");
  Sound wallHit = LoadSound("assets/audio/wall_hit.wav");
  Sound score = LoadSound("assets/audio/score.wav");

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
    const GameEvents events = gameLogic.Update(state, playerInput, GetFrameTime());
    if (events.paddleHit) PlaySound(paddleHit);
    if (events.wallHit) PlaySound(wallHit);
    if (events.pointScored) PlaySound(score);
    renderer.Draw(state);
  }

  UnloadSound(paddleHit);
  UnloadSound(wallHit);
  UnloadSound(score);
  CloseAudioDevice();
  CloseWindow();
}
