#pragma once

// Include
#include <sys/_stdint.h>
#include "Point.hpp"
#include "Body.hpp"
#include "Game.hpp"
#include "GameObjectType.hpp"

// Forward declaration
class Game;

// Class GameObject
class GameObject
{
public:
  explicit GameObject(Game* game);
  virtual ~GameObject() = default;

  virtual void render();
  virtual void update(int deltaTime);
  virtual void intersect(GameObject* object, Side side);
  void doDamage(int damage);

  void setType(const GameObjectType type) { m_body.setType(type); }
  [[nodiscard]] GameObjectType getType() const { return m_body.getType(); }

  void setX(const float x) { m_body.setX(x); }
  void setY(const float y) { m_body.setY(y); }
  void setPoint(const Point<float>& point) { m_body.setTopLeft(point); }
  [[nodiscard]] Point<float> getPoint() const { return m_body.getTopLeft(); }

  void setBody(const Body& body) { m_body = body; }
  [[nodiscard]] Body getBody() const { return m_body; }

  void setHealth(const uint8_t health) { m_health = health; }
  [[nodiscard]] uint8_t getHealth() const { return m_health; }

  void setSpeedV(const Point<float> speed) { m_speedV = speed; }
  [[nodiscard]] Point<float> getSpeedV() const { return m_speedV; }

  void setInvulnerable(const bool invulnerable) { m_invulnerable = invulnerable; }

protected:
  Game* m_game;

  Body m_body;
  Point<float> m_speedV;

  uint8_t m_health;
  bool m_invulnerable;
};
