#pragma once

// Include
#include "GameObject.hpp"

// Class Human
class Human : public GameObject
{
protected:
  explicit Human(Game* game);
  void render() override;
  void update(int deltaTime) override;
  void updateSprite();
  void move(const Point<float>& speedLevel);
  bool fire();
#ifdef DEBUG
  float distanceToHuman(Point<float> currentPoint, 
                        Point<float> currentDirection, 
                        GameObjectType humanType, 
                        Array<Point<float>, kHumanMaxBulletIntersects>& bulletIntersects) const;
#else
  [[nodiscard]] float distanceToHuman(Point<float> currentPoint, 
                                      Point<float> currentDirection, 
                                      GameObjectType humanType) const;
#endif
  static Point<float> reflect(const Point<float>& incident, const Point<float>& normal);
  static float calculateAngle(const Point<float>& a, const Point<float>& b);
  [[nodiscard]] Point<float> calculateFrontCellPosition() const;
  static float calcSin(float angle);
  static float calcCos(float angle);

public:
  void intersect(GameObject* object, Side side) override;
  void setSpeed(const float speed) { m_speed = speed; }
  void setRechargeTime(const int time) { m_rechargeTime = time; }
  void setMaximumFireDistance(const float distance) { m_maxFireDistance = distance; }
  void setInvulnerableTime(const int time) { m_invulnerableTime = time; }

private:
  void checkIntersectsWithSide(Side side,
    Point<float> currentDirection,
    Point<float> currentPoint, 
    float& closestDistance, 
    const Body& rect,
    GameObjectType& targetType,
    Point<float>& closestNormal) const;

protected:
  GUI_MEMDEV_Handle* m_hDst;
  IMAGE* m_sprite;
  size_t m_indexOfSpriteDamaged;
  size_t m_indexOfSprite;
  float m_angle;
  int m_rechargeTime;
  int m_startRechargeTime;
  int m_fireCooldownTime;
  float m_speed;
  float m_startSpeed;
  int m_invulnerableTime;
  float m_maxFireDistance;
};