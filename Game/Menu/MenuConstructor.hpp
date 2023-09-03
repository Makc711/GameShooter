#pragma once

// Include
#include "Game.hpp"
#include "Button.hpp"

// Forward declaration
class Game;
class MenuObject;
class GameObject;

// class MenuConstructor
class MenuConstructor
{
private:
  enum MenuState
  {
    MenuState_MainMenu,
    MenuState_Options,
    MenuState_About
  };

  struct GameDataToSave
  {
    Array<Body, kGameMaxNumOfObstaclesOnLevel> levelBodies;
    uint8_t playerPoints;
    uint8_t enemyPoints;
    bool isPlayerDied;
    bool isEnemiesDied;
  };

public:
  explicit MenuConstructor(Game* game);
  ~MenuConstructor();
  void render() const;
  void update();
  [[nodiscard]] bool isStateMainMenu() const { return m_menuState == MenuState_MainMenu; }
  void setGameBodies();

private:
  void createMenuObjects();
  void checkFlashCard();
  void loadSavedGame();
  void loadGameData();
  void saveGameData();
  void createGameData();
  void renderMainMenu() const;
  void renderOptions() const;
  void renderAbout() const;
  void updateMainMenu();
  void updateButtonActiveState(Button* button) const;
  void updateOptions();
  void updateAbout();

private:
  Game* m_game;
  Array<MenuObject*, kMainMenuButtonsCountMax> m_mainMenuObjects;
  Array<MenuObject*, kOptionsObjectsCountMax> m_optionsObjects;
  Button* m_buttonAboutBack;
  MenuState m_menuState;
  bool m_isSdCardDetected;
  bool m_isSaveCreated;
  const char* m_nameOfFileSave = "SAVE.DAT";
  GameDataToSave m_gameData{};
};