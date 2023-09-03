#pragma once

// Include
#include <GUI.h>
#include <sys/_stdint.h>
#include "Point.hpp"
#include "Joystick.hpp"
#include "GameObject.hpp"
#include "Image.hpp"
#include "Level.hpp"
#include "MenuConstructor.hpp"
#include "PauseMenu.hpp"

// Global variables
extern GUI_CONST_STORAGE GUI_BITMAP bmEnemyDamaged;
extern GUI_CONST_STORAGE GUI_BITMAP bmEnemy;
extern GUI_CONST_STORAGE GUI_BITMAP bmEnemyBullet;
extern GUI_CONST_STORAGE GUI_BITMAP bmPlayerDamaged;
extern GUI_CONST_STORAGE GUI_BITMAP bmPlayer;
extern GUI_CONST_STORAGE GUI_BITMAP bmPlayerBullet;
extern GUI_CONST_STORAGE GUI_BITMAP bmHeart;
extern GUI_CONST_STORAGE GUI_BITMAP bmShield;
extern GUI_CONST_STORAGE GUI_BITMAP bmSpeed;
extern GUI_CONST_STORAGE GUI_BITMAP bmStar;
extern GUI_CONST_STORAGE GUI_BITMAP bmWoodenBox;

// Forward declaration
class GameObject;
class MenuConstructor;
class PauseMenu;
class Level;

// Global function prototypes
void GameError(const char *s);

// Class Game
class Game
{
public:
  enum GameState
  {
    GameState_Menu,
    GameState_Play,
    GameState_Pause
  };

public:
  Game();
  ~Game();

  void pushBodiesToList();
  void deleteLastBodiesFromList();
  static int getImage(IMAGE &pImage);
  void setupSystem();
  void initialize();
  bool loop();
  void shutdown();
  void resetGameProgress();
  GameObject* createObject(const Body& body);
  bool moveObjectTo(GameObject* object, Point<float> newTopLeft) const;
  void addEnemy(GameObject* enemy);
  void pushBlocksBodiesToList();
  void setLevel(Level* level);
  
  void setGameState(const GameState state) { m_gameState = state; }
  void returnToPreviousState() { m_gameState = m_previousGameState; }

  void setPlayer(GameObject* player) { m_player = player; }
  [[nodiscard]] GameObject* getPlayer() const { return m_player; }

  size_t findIndexOfSprite(const GUI_BITMAP* targetBmp) const;
  IMAGE* getSprite(const size_t index) { return &m_sprites[index]; }
  GUI_MEMDEV_Handle* getHDst() { return &m_hDst; }

  void setPlayerPoints(const uint8_t value) { m_playerPoints = value; }
  [[nodiscard]] uint8_t getPlayerPoints() const { return m_playerPoints; }
  void setEnemyPoints(const uint8_t value) { m_enemyPoints = value; }
  [[nodiscard]] uint8_t getEnemyPoints() const { return m_enemyPoints; }
  [[nodiscard]] Joystick* getJoystick() const { return m_joystick; }

  [[nodiscard]] const auto& getObjects() const { return m_objects; }
  [[nodiscard]] const auto& getBodies() const { return m_levelBodies; }
  [[nodiscard]] size_t getBlocksCount() const { return m_blocksCount; }
  [[nodiscard]] bool isGameInProcess() const { return m_isGameInProcess; }
  void setGameNotInProcess() { m_isGameInProcess = false; }
  void setPrintFps(const bool print) { m_isPrintFps = print; }
  void setPlayerDiedState(const bool value) { m_isPlayerDied = value; }
  [[nodiscard]] bool isPlayerDied() const { return m_isPlayerDied; }
  void setEnemiesDiedState(const bool value) { m_isEnemiesDied = value; }
  [[nodiscard]] bool isEnemiesDied() const { return m_isEnemiesDied; }

private:
  void loadTextures();
  int timeBetweenFrames();
  int prepareDisplayForDrawing();
  void render() const;
  void drawText() const;
  bool isPauseButtonPressed();
  void update(int deltaTime);
  static void printFPS(int deltaTime);
  static bool checkBorder(const GameObject* object, Point<float>& newTopLeft);
  GameObject* checkIntersects(const GameObject* exceptObject, Point<float>& newTopLeft, Side& side) const;

private:
  bool m_isGameActive;
  Array<GameObject*, kGameObjectsCountMax> m_objects;
  Array<Body, kGameMaxNumOfObstaclesOnLevel> m_levelBodies;
  size_t m_blocksCount;
  IMAGE m_sprites[kGameNumberOfSprites]
  {
    { &bmEnemyDamaged, 0, 0, 0 },
    { &bmEnemy, 0, 0, 0 },
    { &bmEnemyBullet, 0, 0, 0 },
    { &bmPlayerDamaged, 0, 0, 0 },
    { &bmPlayer, 0, 0, 0 },
    { &bmPlayerBullet, 0, 0, 0 },
    { &bmHeart, 0, 0, 0 },
    { &bmShield, 0, 0, 0 },
    { &bmSpeed, 0, 0, 0 },
    { &bmStar, 0, 0, 0 },
    { &bmWoodenBox, 0, 0, 0 }
  };
  GameObject* m_player;
  Array<GameObject*, kGameMaxEnemiesOnLevel> m_enemies;
  uint8_t m_playerPoints;
  uint8_t m_enemyPoints;
  bool m_isPlayerDied;
  bool m_isEnemiesDied;
  GameState m_gameState;
  GameState m_previousGameState;
  MenuConstructor* m_menuConstructor;
  PauseMenu* m_pauseMenu;
  Level* m_level;
  Joystick* m_joystick;
  GUI_TIMER_TIME m_timeLastFrame;
  bool m_isGameInProcess;
  bool m_isPrintFps;

  GUI_MEMDEV_Handle m_hDst;
  GUI_MEMDEV_Handle m_hLCD;
};
