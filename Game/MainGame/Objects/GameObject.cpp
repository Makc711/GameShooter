// Include
#include "GameObject.hpp"

// Class GameObject
GameObject::GameObject(Game* game)
{
  m_game = game;

  m_body = Body();
  m_speedV = Point<float>();

  m_health = 1;
  m_invulnerable = false;
}

void GameObject::render()
{

}

void GameObject::update(const int deltaTime)
{
  const auto bodyTopLeft = m_body.getTopLeft();
  const auto oldIntP = bodyTopLeft.cast<int>();
  const auto newP = bodyTopLeft + (m_speedV * static_cast<float>(deltaTime));
  const auto newIntP = newP.cast<int>();

  if (oldIntP.x != newIntP.x)
  {
    m_game->moveObjectTo(this, { newP.x, bodyTopLeft.y });
  }
  else 
  {
    m_body.setX(newP.x);
  }

  if (oldIntP.y != newIntP.y)
  {
    m_game->moveObjectTo(this, { m_body.getTopLeft().x, newP.y });
  }
  else 
  {
    m_body.setY(newP.y);
  }
}

void GameObject::intersect(GameObject* object, Side side)
{

}

void GameObject::doDamage(const int damage)
{
  if (m_invulnerable) 
  {
    return;
  }
  if (m_health > damage) 
  {
    m_health -= damage;
  }
  else 
  {
    m_health = 0;
  }
}