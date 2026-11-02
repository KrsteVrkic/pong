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

  // Escape is used for in-game navigation, not to close the window.
  SetExitKey(KEY_NULL);
  
  ChangeDirectory(GetApplicationDirectory());
  InitAudioDevice();
  SetTargetFPS(60);

  Sound paddleHit = LoadSound("assets/audio/paddle_hit.wav");
  Sound wallHit = LoadSound("assets/audio/wall_hit.wav");
  Sound score = LoadSound("assets/audio/score.wav");
  constexpr float soundVolumeMinus6Db = 0.501187f;
  SetSoundVolume(paddleHit, soundVolumeMinus6Db);
  SetSoundVolume(wallHit, soundVolumeMinus6Db);
  SetSoundVolume(score, soundVolumeMinus6Db);

  GameState state;
  Input input;
  GameLogic gameLogic;
  Renderer renderer;
  MainMenu mainMenu;

  GameMode gameMode = GameMode::MainMenu;
  bool shouldQuit = false;

  while (!WindowShouldClose() && !shouldQuit) {
    switch (gameMode) {

    case GameMode::MainMenu: {
      const MainMenuAction action = mainMenu.Update();
      mainMenu.Draw();
      switch (action) {
        case MainMenuAction::Play:
          state = GameState{};
          gameMode = GameMode::Playing;
          break;
        case MainMenuAction::Settings:
          gameMode = GameMode::Settings;
          break;
        case MainMenuAction::Quit:
          shouldQuit = true;
          break;
        case MainMenuAction::None:
          break;
      }
      break;
    }

    case GameMode::Settings: {
      if (IsKeyPressed(KEY_ESCAPE)) gameMode = GameMode::MainMenu;
      mainMenu.DrawSettings();
      break;
    }

    case GameMode::Playing: {
      if (IsKeyPressed(KEY_ESCAPE)) {
        gameMode = GameMode::MainMenu;
        break;
      }

      if (IsKeyPressed(KEY_SPACE)) {
        gameMode = GameMode::Paused;
        renderer.Draw(state, true);
        break;
      }

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

    case GameMode::Paused: {
      const bool resume = IsKeyPressed(KEY_SPACE);
      const bool returnToMenu = IsKeyPressed(KEY_ESCAPE);
      renderer.Draw(state, true);
      if (resume) gameMode = GameMode::Playing;
      if (returnToMenu) gameMode = GameMode::MainMenu;
      break;
    }

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
