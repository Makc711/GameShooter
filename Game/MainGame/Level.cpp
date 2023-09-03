// Include
#include "Level.hpp"
#include <LCD.h>
#include "rng.h"
#include "GameObject.hpp"
#include "Human.hpp"
#include "Enemy.hpp"

// Class Level
Level::Level(Game* game)
{
  m_game = game;
}

Level::~Level()
{
  m_game->shutdown();
}

void Level::createLevelObjects() const
{
  createBlockJoystick();
  const size_t blocksOnLevel = getRandom(kBlocksOnLevelMin, kBlocksOnLevelMax);
  for (size_t i = 0; i < blocksOnLevel; i++) 
  {
    createBlock();
  }
  createPlayer();
  createEnemies();
  createBonus();
}

void Level::createLevelObjectsFromBodies(const Array<Body, kGameMaxNumOfObstaclesOnLevel>& bodies, const uint8_t level) const
{
  for (Body body : bodies)
  {
    switch (body.getType())
    {
    case GameObjectType_Block:
      if (body.getTopLeft().x < kHumanSize)
      {
        body.setType(GameObjectType_BlockJoystick);
      }
      m_game->createObject(body);
      break;
    case GameObjectType_Bonus: 
      m_game->createObject(body);
      break;
    case GameObjectType_Player:
      {
        const auto player = m_game->createObject(body);
        m_game->setPlayer(player);
        break;
      }
    case GameObjectType_Enemy:
      {
        const auto enemy = dynamic_cast<Enemy*>(m_game->createObject(body));
        enemy->setSpeed(m_levelSettings[level].m_enemySpeed);
        enemy->setHealth(m_levelSettings[level].m_enemyHealth);
        enemy->setMaximumFireDistance(m_levelSettings[level].m_maximumFireDistance);
        enemy->setRechargeTime(m_levelSettings[level].m_rechargeTime);
        m_game->addEnemy(enemy);
        break;
      }
    default: ;
    }
  }
}

void Level::createBlockJoystick() const
{
  const auto point = Point<float>(kJoystickBorder - 2, 
    static_cast<float>(LCD_GetYSize() - 1 - kJoystickBorder - kJoystickRadius * 2 - 2));
  constexpr Size size = { kJoystickRadius * 2 + 5, kJoystickRadius * 2 + 5 };
  const auto body = Body(point, size, GameObjectType_BlockJoystick);
  m_game->createObject(body);
}

void Level::createBlock() const
{
  for (size_t i = 0; i < kLevelAttemptsToCreateBlock; i++) 
  {
    const auto width = static_cast<uint16_t>(getRandom(kLevelBlockSizeMin, kLevelBlockSizeMax));
    const auto height = static_cast<uint16_t>(getRandom(kLevelBlockSizeMin, kLevelBlockSizeMax));
    constexpr int border = kHumanSize * 3 / 2;
    const auto point = Point<float>(
      static_cast<float>(getRandom(border, LCD_GetXSize() - width - border)),
      static_cast<float>(getRandom(border, LCD_GetYSize() - height - border)));
    const Size size = { static_cast<float>(width), static_cast<float>(height) };
    const auto body = Body(point, size, GameObjectType_Block);
    if (m_game->createObject(body)) 
    {
      break;
    }
  }
}

void Level::createPlayer() const
{
  const auto player = createHuman(GameObjectType_Player);
  m_game->setPlayer(player);
}

void Level::createEnemies() const
{
  const auto level = m_game->getPlayerPoints();
  for (size_t i = 0; i < m_levelSettings[level].m_enemiesOnLevel; i++)
  {
    const auto enemy = dynamic_cast<Enemy*>(createHuman(GameObjectType_Enemy));
    enemy->setSpeed(m_levelSettings[level].m_enemySpeed);
    enemy->setHealth(m_levelSettings[level].m_enemyHealth);
    enemy->setMaximumFireDistance(m_levelSettings[level].m_maximumFireDistance);
    enemy->setRechargeTime(m_levelSettings[level].m_rechargeTime);
    m_game->addEnemy(enemy);
  }
}

GameObject* Level::createHuman(const GameObjectType objectType) const
{
  GameObject* human = nullptr;
  while (human == nullptr)
  {
    auto point = Point<float>(getRandomCoordinate(kHumanSize, LCD_GetXSize() / 2), 
      getRandomCoordinate(kHumanSize, LCD_GetYSize()));
    if (objectType == GameObjectType_Enemy)
    {
      point.x += static_cast<float>(LCD_GetXSize()) / 2.0f;
    }
    const auto body = Body(point, { kHumanSize, kHumanSize }, objectType);
    human = m_game->createObject(body);
  }
  return human;
}

void Level::createBonus() const
{
  const GameObject* bonus = nullptr;
  const IMAGE* sprite = m_game->getSprite(m_game->findIndexOfSprite(&bmWoodenBox));
  
  while (bonus == nullptr)
  {
    const auto point = Point<float>(getRandomCoordinate(sprite->width, LCD_GetXSize()), 
                                    getRandomCoordinate(sprite->height, LCD_GetYSize()));
    const Size bonusSize = { static_cast<float>(sprite->width), static_cast<float>(sprite->height) };
    const auto body = Body(point, bonusSize, GameObjectType_Bonus);
    bonus = m_game->createObject(body);
  }
}

uint32_t Level::getRandom(const uint32_t min, const uint32_t max)
{
  return min + HAL_RNG_GetRandomNumber(&hrng) % (max - min + 1);
}

float Level::getRandomCoordinate(const uint16_t objectSize, const int lcdSize)
{
  return static_cast<float>(getRandom(0, lcdSize - objectSize));
}