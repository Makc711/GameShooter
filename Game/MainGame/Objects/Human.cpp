// Include
#include "Human.hpp"
#include <cmath>
#include "Bonus.hpp"
#include "Bullet.hpp"
#include "GUI.h"

// Class Human
Human::Human(Game* game)
  : GameObject(game)
{
  m_hDst = game->getHDst();
  m_indexOfSpriteDamaged = 0;
  m_indexOfSprite = 0;
  m_sprite = m_game->getSprite(m_indexOfSprite);
  m_angle = static_cast<float>(Level::getRandom(0, 360));
  m_rechargeTime = 0;
  m_fireCooldownTime = 0;
  m_speed = 0;
  m_startSpeed = 0;
  m_startRechargeTime = 0;
  m_invulnerableTime = 0;
  m_maxFireDistance = kHumanMaxFireDistance;
}

void Human::render()
{
  const auto center = m_body.getCenter();
  GUI_MEMDEV_RotateHQ(m_sprite->hMem,
    *m_hDst,
    static_cast<int>(center.x - static_cast<float>(m_sprite->width) / 2.0f), 
    static_cast<int>(center.y - static_cast<float>(m_sprite->height) / 2.0f), 
    static_cast<int>(-m_angle * 1000.0f), 
    1000);

  const IMAGE* sprite = nullptr;
  if (m_startSpeed == 0.0f)
  {
    m_startSpeed = m_speed;
  }

  if (m_startRechargeTime == 0)
  {
    m_startRechargeTime = m_rechargeTime;
  }

  if (m_health > 2)
  {
    sprite = m_game->getSprite(Bonus::BonusId_Heart);
  }

  if (m_invulnerable)
  {
    sprite = m_game->getSprite(Bonus::BonusId_Shield);
  }

  if (m_speed > m_startSpeed)
  {
    sprite = m_game->getSprite(Bonus::BonusId_Speed);
  }

  if (m_rechargeTime < m_startRechargeTime)
  {
    sprite = m_game->getSprite(Bonus::BonusId_Star);
  }

  if (sprite)
  {
    GUI_MEMDEV_RotateHQ(sprite->hMem,
      *m_hDst,
      static_cast<int>(center.x - static_cast<float>(sprite->width) / 2.0f), 
      static_cast<int>(center.y - static_cast<float>(sprite->height) / 2.0f), 
      0, 
      500);
  }
}

void Human::update(const int deltaTime)
{
  GameObject::update(deltaTime);
  updateSprite();

  if (m_fireCooldownTime > 0) 
  {
    m_fireCooldownTime -= deltaTime;
  }

  if (m_invulnerableTime > 0) 
  {
    m_invulnerableTime -= deltaTime;
  }
  else 
  {
    m_invulnerable = false;
  }
}

void Human::updateSprite()
{
  m_sprite = (m_health == 1)
            ? m_game->getSprite(m_indexOfSpriteDamaged)
            : m_game->getSprite(m_indexOfSprite);
}

void Human::move(const Point<float>& speedLevel)
{
  m_speedV = speedLevel * m_speed;
}

bool Human::fire()
{
  if (m_fireCooldownTime > 0) 
  {
    return false;
  }
  
  const Point<float> point = calculateFrontCellPosition() - (static_cast<float>(kBulletSize) / 2.0f);
  const auto body = Body(point, { kBulletSize, kBulletSize }, GameObjectType_Bullet);
  if (auto* bullet = dynamic_cast<Bullet*>(m_game->createObject(body)))
  {
    bullet->setOwnerObject(this);
    bullet->setSprite();
    bullet->setSpeedV({ kBulletSpeed * calcCos(m_angle), kBulletSpeed * calcSin(m_angle) });
    m_fireCooldownTime = m_rechargeTime;
    return true;
  }
  return false;
}

float Human::calcSin(const float angle)
{
  return std::sin(static_cast<float>(M_PI) * angle / 180.0f);
}

float Human::calcCos(const float angle)
{
  return std::cos(static_cast<float>(M_PI) * angle / 180.0f);
}

Point<float> Human::calculateFrontCellPosition() const
{
  constexpr float radius = kHumanSize / 2.0f + kHumanGunSize + kBulletSize / 2.0f;
  const Point<float> center = m_body.getCenter();
  const float x = center.x + calcCos(m_angle) * radius;
  const float y = center.y + calcSin(m_angle) * radius;
  return {x, y};
}

Point<float> Human::reflect(const Point<float>& incident, const Point<float>& normal)
{
  const float dot2 = incident.dot(normal) * 2;
  Point<float> reflected = incident - (normal * dot2);
  return reflected.normalize();
}

float Human::calculateAngle(const Point<float>& a, const Point<float>& b)
{
  return std::atan2(b.y - a.y, b.x - a.x) * 180.0f / static_cast<float>(M_PI);
}

void Human::checkIntersectsWithSide(const Side side,
  Point<float> currentDirection,
  Point<float> currentPoint, 
  float& closestDistance, 
  const Body& rect,
  GameObjectType& targetType,
  Point<float>& closestNormal) const
{
  constexpr float epsilon = 0.0001f;
  Point<float> rectTopLeft = rect.getTopLeft();
  Point<float> rectBottomRight = rect.getBottomRight();
  float a = rectTopLeft.x;
  Point<float> normal = { -1.0f, 0.0f };
  switch (side)
  {
  case Side_Left: 
    break;
  case Side_Right: 
    a = rectBottomRight.x;
    normal = { 1.0f, 0.0f };
    break;
  case Side_Bottom:
    a = rectTopLeft.y;
    normal = { 0.0f, -1.0f };
    currentDirection.swap();
    currentPoint.swap();
    rectTopLeft.swap();
    rectBottomRight.swap();
    break;
  case Side_Top:
    a = rectBottomRight.y;
    normal = { 0.0f, 1.0f };
    currentDirection.swap();
    currentPoint.swap();
    rectTopLeft.swap();
    rectBottomRight.swap();
    break;
  case Side_None:
    GameError("Error in Human::checkIntersectsWithSide. Invalid case!");
    break;
  }

  const float edgeDistance = currentDirection.x != 0.0f
                                   ? (a - currentPoint.x) / currentDirection.x
                                   : m_maxFireDistance;
  if (edgeDistance > epsilon && edgeDistance < closestDistance) 
  {
    const Point<float> intersection = { a, currentPoint.y + edgeDistance * currentDirection.y };
    if (intersection.y >= rectTopLeft.y && intersection.y <= rectBottomRight.y) 
    {
      closestDistance = edgeDistance;
      closestNormal = normal;
      targetType = rect.getType();
    }
  }
}

#ifdef DEBUG
float Human::distanceToHuman(Point<float> currentPoint, 
                             Point<float> currentDirection, 
                             const GameObjectType humanType, 
                             Array<Point<float>, kHumanMaxBulletIntersects>& bulletIntersects) const
#else
float Human::distanceToHuman(Point<float> currentPoint, 
                             Point<float> currentDirection, 
                             const GameObjectType humanType) const
#endif
{
  const GameObjectType originType = (humanType == GameObjectType_Player)
                                    ? GameObjectType_Enemy
                                    : GameObjectType_Player;
  float totalDistance = 0.0f;

  while (totalDistance < m_maxFireDistance) 
  {
    float closestDistance = m_maxFireDistance;
    Point<float> closestNormal;
    GameObjectType targetType = GameObjectType_None;
    const auto levelBodies = m_game->getBodies();
    for (const auto& rect : levelBodies)
    {
      checkIntersectsWithSide(Side_Left,
        currentDirection,
        currentPoint, 
        closestDistance, 
        rect,
        targetType,
        closestNormal);

      checkIntersectsWithSide(Side_Right,
        currentDirection,
        currentPoint, 
        closestDistance, 
        rect,
        targetType,
        closestNormal);

      checkIntersectsWithSide(Side_Bottom,
        currentDirection,
        currentPoint, 
        closestDistance, 
        rect,
        targetType,
        closestNormal);

      checkIntersectsWithSide(Side_Top,
        currentDirection,
        currentPoint, 
        closestDistance, 
        rect,
        targetType,
        closestNormal);
    }

    if (closestDistance < m_maxFireDistance) 
    {
      if ((targetType == GameObjectType_Bonus) || (targetType == originType))
      {
        return -1;
      }
      totalDistance += closestDistance;
      currentPoint = currentPoint + (currentDirection * closestDistance);

#ifdef DEBUG
      if (bulletIntersects.isFull())
      {
        return -1;
      }
      bulletIntersects.pushBack(currentPoint);
#endif

      if (targetType == GameObjectType_Block)
      {
        currentDirection = reflect(currentDirection, closestNormal);
      }
      else if (targetType == humanType)
      {
        return totalDistance;
      }
    }
    else 
    {
      return -1;
    }
  }
  return -1;
}

void Human::intersect(GameObject* object, Side side)
{
  // I don't check for intersection with the Bullet since Human can't move faster than the bullet
  if ((object->getType() == GameObjectType_Bonus) && (object->getHealth() == 1))
  {
    dynamic_cast<Bonus*>(object)->giveImprovement(*this);
    object->setHealth(0);
  }
}