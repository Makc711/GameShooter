#pragma once

// Include
#include "Game.hpp"
#include "Button.hpp"

// Forward declaration
class Game;

// class PauseMenu
class PauseMenu
{
public:
  enum Id
  {
    Id_NextLevel,
    Id_MainMenu,
    Id_Retry
  };

public:
  explicit PauseMenu(Game *game);
  ~PauseMenu();
  void render() const;
  void update() const;
  void setId(Id id);

private:
  Game* m_game;
  Button* m_button;
  Id m_id;
};