#pragma once

enum class MainMenuAction {
  None,
  Play,
  Settings,
  Quit
};

class MainMenu {
public:
  MainMenuAction Update();
  void Draw() const;
  void DrawSettings() const;

private:
  int selectedOption{0};
};

