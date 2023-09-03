#pragma once

// Include
#include <sys/_stdint.h>
#include "Array.hpp"
#include "Body.hpp"
#include "GameObject.hpp"
#include "GameObjectType.hpp"

// Forward declaration
class Game;
class GameObject;

// Class Level
class Level
{
public:
  explicit Level(Game* game);
  ~Level();
  static uint32_t getRandom(uint32_t min, uint32_t max);
  void createLevelObjects() const;
  void createLevelObjectsFromBodies(const Array<Body, kGameMaxNumOfObstaclesOnLevel>& bodies, uint8_t level) const;

private:
  void createBlockJoystick() const;
  void createBlock() const;
  void createPlayer() const;
  void createEnemies() const;
  void createBonus() const;
  [[nodiscard]] GameObject* createHuman(GameObjectType objectType) const;
  static float getRandomCoordinate(uint16_t objectSize, int lcdSize);

private:
  typedef struct
  {
    size_t m_enemiesOnLevel;
    float m_enemySpeed;
    uint8_t m_enemyHealth;
    int m_rechargeTime;
    float m_maximumFireDistance;
  } LevelSettings;

  Game* m_game;
  LevelSettings m_levelSettings[kNumberOfLevels]
  {
    { 1, 0.03f, 1, 1500, 1000 },
    { 1, 0.03f, 2, 1500, 1000 },
    { 1, 0.06f, 2, 1000, 400 },
    { 2, 0.03f, 1, 1500, 1000 },
    { 2, 0.03f, 2, 1500, 400 },
    { 2, 0.06f, 2, 1200, 600 },
    { 2, 0.06f, 2, 1500, 800 },
    { 2, 0.06f, 2, 1400, 1000 },
    { 2, 0.06f, 2, 1200, 1000 },
    { 2, 0.06f, 2, 1000, 1000 }
  };
};