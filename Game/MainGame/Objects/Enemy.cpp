// Include
#include "Enemy.hpp"
#include <cstdio>
#include "Bullet.hpp"
#include "Player.hpp"

// Class Enemy
Enemy::Enemy(Game* game, const Body& body)
  : Human(game)
{
  m_body = body;
  m_invulnerable = true;
  m_invulnerableTime = kEnemyStartWait;
  m_timeBeforeStart = kEnemyStartWait;
  m_timeToEnableFire = kEnemyStartWait;
  m_isMoveToBlockAngle = false;
  m_timeToCheckIntersectWithBlock = 0;
  m_timeFromLastFire = 0;
  m_indexOfSpriteDamaged = m_game->findIndexOfSprite(&bmEnemyDamaged);
  m_indexOfSprite = m_game->findIndexOfSprite(&bmEnemy);
  m_offsetAngle = kEnemyOffsetAngleToVictoryDance;
  m_previousEnemyCenter = { 0, 0 };
  m_currentDistanceToPlayer = m_maxFireDistance;
  m_isReadyToFire = false;
  m_angleTmp = static_cast<uint16_t>(m_angle);
  m_previousBullet = nullptr;
  updateSprite();
}

void Enemy::update(const int deltaTime)
{
  Human::update(deltaTime);

  m_game->pushBodiesToList();
  analyze();
  m_game->deleteLastBodiesFromList();

  if (m_timeToCheckIntersectWithBlock > 0)
  {
    m_timeToCheckIntersectWithBlock -= deltaTime;
  }

  if (m_timeFromLastFire > 0)
  {
    m_timeFromLastFire -= deltaTime;
  }

  if (m_timeToEnableFire > 0)
  {
    m_timeToEnableFire -= deltaTime;
  }
  
  if (m_timeBeforeStart > 0)
  {
    m_timeBeforeStart -= deltaTime;
  }
}

void Enemy::intersect(GameObject* object, const Side side)
{
  Human::intersect(object, side);

  const Body blockBody = object->getBody();
  const Point<float> blockTopLeft = blockBody.getTopLeft();
  if ((object->getType() == GameObjectType_Block) && (blockTopLeft.x >= kHumanSize))
  {
    if (m_timeToCheckIntersectWithBlock <= 0)
    {
      m_timeToCheckIntersectWithBlock = kEnemyTimeToCheckIntersectWithBlock;
      const Point<float> enemyCenter = m_body.getCenter();
      const float deltaX = m_previousEnemyCenter.x - enemyCenter.x;
      const float deltaY = m_previousEnemyCenter.y - enemyCenter.y;

      m_previousEnemyCenter = enemyCenter;
      if ((std::abs(deltaX) < 1.0f) || (std::abs(deltaY) < 1.0f))
      {
        const Point<float> blockBottomRight = blockBody.getBottomRight();
        const Point<float> enemyBlockDelta = enemyCenter - blockBody.getCenter();
        if (const auto player = m_game->getPlayer())
        {
          const Point<float> playerCenter = player->getBody().getCenter();
          constexpr float halfHumanSize = kHumanSize / 2.0f;
          constexpr float border = halfHumanSize + 4.0f;
          float blockAngleX = playerCenter.x;
          float blockAngleY = playerCenter.y;

          switch (side)
          {
          case Side_Left: 
            blockAngleX = blockTopLeft.x - halfHumanSize;
            blockAngleY = (enemyBlockDelta.y >= 0)
                                ? blockBottomRight.y + border
                                : blockTopLeft.y - border;
            break;
          case Side_Top: 
            blockAngleX = (enemyBlockDelta.x >= 0)
                                ? blockBottomRight.x + border
                                : blockTopLeft.x - border;
            blockAngleY = blockTopLeft.y - halfHumanSize;
            break;
          case Side_Right: 
            blockAngleX = blockBottomRight.x + halfHumanSize;
            blockAngleY = (enemyBlockDelta.y >= 0)
                                ? blockBottomRight.y + border
                                : blockTopLeft.y - border;
            break;
          case Side_Bottom: 
            blockAngleX = (enemyBlockDelta.x >= 0)
                                ? blockBottomRight.x + border
                                : blockTopLeft.x - border;
            blockAngleY = blockBottomRight.y + halfHumanSize;
            break;
          case Side_None:
            GameError("Error in Enemy::intersect. Invalid case!");
            break;
          }
          m_blockAnglePoint.x = blockAngleX;
          m_blockAnglePoint.y = blockAngleY;
          m_isMoveToBlockAngle = true;
        }
      }
    }
  }
}

void Enemy::analyze()
{
  float currentAngle = m_angle;

  for (const uint16_t angEnd = m_angleTmp; m_angleTmp < angEnd + kEnemyDegreesPerCycle; m_angleTmp++)
  {
    m_angle = m_angleTmp;
    const Point<float> gunPoint = calculateFrontCellPosition();
    if (isIntersectsPointWithBodies(gunPoint))
    {
      m_angle = currentAngle;
      continue;
    }
    const Point<float> direction = (gunPoint - m_body.getCenter()).normalize();
    
#ifdef DEBUG
    Array<Point<float>, kHumanMaxBulletIntersects> bulletIntersects;
    const float distance = distanceToHuman(gunPoint, direction, GameObjectType_Player, bulletIntersects);
#else
    const float distance = distanceToHuman(gunPoint, direction, GameObjectType_Player);
#endif
    
    m_angle = currentAngle;

    if ((distance >= kBulletSize) && (distance <= m_currentDistanceToPlayer)) 
    {
      m_isReadyToFire = true;
      if (distance < m_currentDistanceToPlayer)
      {
        m_currentDistanceToPlayer = distance;
        currentAngle = m_angleTmp;
        m_angle = currentAngle;
      }
      
#ifdef DEBUG
      if (distance >= kBulletSize)
      {
        GUI_SetColor(GUI_RED);
        Point<float> prevPoint = gunPoint;
        for (auto& point : bulletIntersects)
        {
          GUI_DrawLine(
            static_cast<int>(prevPoint.x), 
            static_cast<int>(prevPoint.y), 
            static_cast<int>(point.x), 
            static_cast<int>(point.y));
          prevPoint = point;
        }

        GUI_SetColor(GUI_RED);
        GUI_SetFont(&GUI_Font8_ASCII);
        GUI_SetTextMode(GUI_TM_TRANS);
        char str[4];
        sprintf(str, "%3i", static_cast<int>(distance));
        GUI_DispStringAt(str, LCD_GetXSize() - 30, 5);
      }
#endif
    }
  }

  if (m_angleTmp >= static_cast<uint16_t>(m_angle + 360))
  {
    if (m_angle >= 360)
    {
      m_angle = static_cast<float>(static_cast<uint16_t>(m_angle) % 360);
    }
    m_angleTmp = static_cast<uint16_t>(m_angle);
    m_currentDistanceToPlayer = m_maxFireDistance;
    m_isReadyToFire = false;
  }

  bool isDefendSelf = false;
  const Point<float> playerBulletCenter = findPlayerBulletInArea();
  const Point<float> bodyCenter = m_body.getCenter();
  if (playerBulletCenter != bodyCenter)
  {
    m_angle = calculateAngle(bodyCenter, playerBulletCenter);
    isDefendSelf = true;
  }

  if (m_timeBeforeStart <= 0)
  {
    if (isDefendSelf) 
    {
      fire();
      return;
    }

    if (m_isReadyToFire)
    {
      if (m_timeToEnableFire <= 0)
      {
        if (const auto player = dynamic_cast<Player*>(m_game->getPlayer()))
        {
          m_timeToEnableFire = static_cast<int>(player->getDistanceToEnemy() / kBulletSpeed);
        }

        m_speedV = { 0, 0 };
        fire();
        m_timeFromLastFire = kEnemyTimeFromLastFire;
      }
    }
    else
    {
      enemyMove();
    }
  }
}

Point<float> Enemy::findPlayerBulletInArea()
{
  float distanceToBullet2 = kHumanMaxFireDistance;
  const Point<float> bodyCenter = m_body.getCenter();
  Bullet* bulletInArea = nullptr;
  const auto& gameObjects = m_game->getObjects();
  for (size_t i = m_game->getBlocksCount(); i < gameObjects.count(); i++)
  {
    const auto gameObjectBody = gameObjects[i]->getBody();
    if (gameObjectBody.getType() == GameObjectType_Bullet)
    {
      const auto bullet = dynamic_cast<Bullet*>(gameObjects[i]);
      if (bullet->getOwnerObject()->getBody().getType() != GameObjectType_Enemy)
      {
        Body area = m_body;
        area.addBorder(kEnemyAreaBorder);
        const Point<float> bulletCenter = bullet->getBody().getCenter();
        if (isPointIntersectRect(bulletCenter, area))
        {
          const float distance = bodyCenter.length2(bulletCenter);
          if (distance < distanceToBullet2)
          {
            distanceToBullet2 = distance;
            bulletInArea = bullet;
          }
        }
      }
    }
  }

  Point<float> result = bodyCenter;
  if (bulletInArea)
  {
    if (bulletInArea == m_previousBullet)
    {
      const Point<float> bulletInAreaCenter = bulletInArea->getBody().getCenter();
      Point<float> vectorAB = bulletInAreaCenter - m_previousBulletInAreaCenter;
      const Point<float> direction = vectorAB.normalize();
    
#ifdef DEBUG
      Array<Point<float>, kHumanMaxBulletIntersects> bulletIntersects;
      const float distanceToEnemy = distanceToHuman(bulletInAreaCenter, direction, GameObjectType_Enemy, bulletIntersects);
#else
      const float distanceToEnemy = distanceToHuman(bulletInAreaCenter, direction, GameObjectType_Enemy);
#endif

      result = (distanceToEnemy > 0) ? bulletInAreaCenter : bodyCenter;


      const Point<float> vectorAC = bodyCenter - m_previousBulletInAreaCenter;
      const float signToMove = sign(vectorAB.x * vectorAC.y - vectorAB.y * vectorAC.x);
      const Point<float> vectorNormal = { vectorAB.y * -signToMove, vectorAB.x * signToMove };
      const Point<float> pointToMove = bulletInAreaCenter + vectorNormal;
      Point<float> speedLevel;
      Point<float>::calculateSinCos(speedLevel.y,
        speedLevel.x,
        bulletInAreaCenter, 
        pointToMove);

      move(speedLevel);
    }
    else
    {
      result = bodyCenter;
      m_speedV = { 0, 0 };
    }
    m_previousBullet = bulletInArea;
    m_previousBulletInAreaCenter = m_previousBullet->getBody().getCenter();
  }
  
  return result;
}

bool Enemy::isIntersectsPointWithBodies(const Point<float>& point) const
{
  const auto levelBodies = m_game->getBodies();
  for (const auto& rect : levelBodies)
  {
    if (isPointIntersectRect(point, rect))
    {
      return true;
    }
  }
  return false;
}

bool Enemy::isPointIntersectRect(const Point<float>& point, const Body& rect)
{
  return (point <= rect.getBottomRight()) && (point >= rect.getTopLeft());
}

void Enemy::enemyMove()
{
  if (m_timeFromLastFire <= 0 && m_isMoveToBlockAngle)
  {
    m_timeFromLastFire = kEnemyTimeFromLastFire;
    m_isMoveToBlockAngle = false;
  }
  else
  {
    moveToPlayer();
  }
}

void Enemy::moveToPlayer()
{
  const Point<float> enemyCenter = m_body.getCenter();
  const auto player = m_game->getPlayer();
  if (player == nullptr)
  {
    victoryDance();
    return;
  }
  const Point<float> playerCenter = player->getBody().getCenter();

  constexpr auto minDistanceToPlayer = kHumanSize + kHumanGunSize + kBulletSize;
  if (enemyCenter.length2(playerCenter) > (minDistanceToPlayer * minDistanceToPlayer))
  {
    if ((std::abs(enemyCenter.x - m_blockAnglePoint.x) < 1) &&
    (std::abs(enemyCenter.y - m_blockAnglePoint.y) < 1))
    {
      m_isMoveToBlockAngle = false;
    }
  
    Point<float> speedLevel;
    Point<float>::calculateSinCos(speedLevel.y,
      speedLevel.x,
      enemyCenter, 
      m_isMoveToBlockAngle ? m_blockAnglePoint : playerCenter);

    move(speedLevel);
  }
  else
  {
    m_speedV = { 0, 0 };
  }
}

void Enemy::victoryDance()
{
  m_rechargeTime = kEnemyRechargeTimeToVictoryDance;
  m_angle = static_cast<float>(static_cast<int>(m_angle));
  fire();
  move({ calcCos(m_angle - 180), calcSin(m_angle - 180) });
  if (m_angle >= 180)
  {
    m_offsetAngle = -kEnemyOffsetAngleToVictoryDance;
  }
  if (m_angle <= -180)
  {
    m_offsetAngle = kEnemyOffsetAngleToVictoryDance;
  }
  m_angle += m_offsetAngle;
}