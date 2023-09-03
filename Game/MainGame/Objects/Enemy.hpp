#pragma once

// Include
#include "Bullet.hpp"
#include "Human.hpp"


// Class Enemy
class Enemy final : public Human
{
public:
  explicit Enemy(Game* game, const Body& body);
  void update(int deltaTime) override;
  void intersect(GameObject* object, Side side) override;
  static bool isPointIntersectRect(const Point<float>& point, const Body& rect);

private:
  void analyze();
  [[nodiscard]] Point<float> findPlayerBulletInArea();
  [[nodiscard]] bool isIntersectsPointWithBodies(const Point<float>& point) const;
  void enemyMove();
  void moveToPlayer();
  void victoryDance();

private:
  int m_timeBeforeStart;
  Point<float> m_blockAnglePoint;
  int m_timeToEnableFire;
  bool m_isMoveToBlockAngle;
  int m_timeToCheckIntersectWithBlock;
  int m_timeFromLastFire;
  float m_offsetAngle;
  Point<float> m_previousEnemyCenter;
  float m_currentDistanceToPlayer;
  bool m_isReadyToFire;
  uint16_t m_angleTmp;
  Bullet* m_previousBullet;
  Point<float> m_previousBulletInAreaCenter{};
};