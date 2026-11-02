#include "Game.hpp"

#include "../core/GameState.hpp"
#include "../gameplay/GameLogic.hpp"
#include "../input/Input.hpp"
#include "../render/Renderer.hpp"
#include "../core/GameMode.hpp"
#include "../ui/MainMenu.hpp"

#include <raylib.h>
#include <algorithm>

void Game::Run() {
  InitWindow(
	     static_cast<int>(GameState::initialFieldWidth),
             static_cast<int>(GameState::sceneHeight),
	     "pong"
	    );
  
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
  MainMenu mainMenu;

  GameMode gameMode = GameMode::MainMenu;

  while (!WindowShouldClose()) {
    switch (gameMode) {

    case GameMode::MainMenu:
      mainMenu.Draw();
      if (mainMenu.Update()) {
        gameMode = GameMode::Playing;
      }
      break;

    case GameMode::Playing: {
      const float scale = std::min(
				   static_cast<float>(GetScreenWidth()) /
				   GameState::initialFieldWidth,
				   static_cast<float>(GetScreenHeight()) /
				   GameState::sceneHeight
				  );

      state.SetFieldWidth(
			  static_cast<float>(GetScreenWidth()) / scale
			 );

      const PlayerInput playerInput = input.Read();

      const GameEvents events = gameLogic.Update(
						 state,
						 playerInput,
						 GetFrameTime()
						);
    
      if (events.paddleHit) PlaySound(paddleHit);
      if (events.wallHit) PlaySound(wallHit);
      if (events.pointScored) PlaySound(score);

      renderer.Draw(state);
      break;
    }  

    case GameMode::Paused:
      break;

    case GameMode::GameOver:
      break;
    }
  }

  UnloadSound(paddleHit);
  UnloadSound(wallHit);
  UnloadSound(score);
  CloseAudioDevice();
  CloseWindow();
}
