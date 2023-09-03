// Include
#include "Bullet.hpp"
#include "Game.hpp"

// Class Bullet
Bullet::Bullet(Game* game, const Body& body)
  : GameObject(game)
{
  m_body = body;
  m_ownerObject = nullptr;
  m_indexOfSpritePlayerBullet = m_game->findIndexOfSprite(&bmPlayerBullet);
  m_indexOfSpriteEnemyBullet = m_game->findIndexOfSprite(&bmEnemyBullet);
  m_sprite = m_game->getSprite(m_indexOfSpriteEnemyBullet);
}

void Bullet::render()
{
  const auto pointTopLeft = m_body.getTopLeft();
  GUI_DrawBitmap(m_sprite->pBitmap, 
    static_cast<int>(pointTopLeft.x), 
    static_cast<int>(pointTopLeft.y));
}

void Bullet::intersect(GameObject* object, Side side)
{
  if (object->getType() == GameObjectType_Block) 
  {
    const Point<float> p0TopLeft = m_body.getTopLeft();
    const Point<float> p0BottomRight = m_body.getBottomRight();

    const auto objectBody = object->getBody();
    const Point<float> p1TopLeft = objectBody.getTopLeft();
    const Point<float> p1BottomRight = objectBody.getBottomRight();

    if (p0TopLeft.x >= p1BottomRight.x || p0BottomRight.x <= p1TopLeft.x) 
    {
      m_speedV.x *= -1;
    }
    else if (p0TopLeft.y >= p1BottomRight.y || p0BottomRight.y <= p1TopLeft.y) 
    {
      m_speedV.y *= -1;
    }
    else 
    {
      m_speedV.x *= -1;
      m_speedV.y *= -1;
    }
  }
  else 
  {
    m_health = 0;
    if (object && m_ownerObject && (object->getType() != m_ownerObject->getType())) 
    {
      object->doDamage(kBulletDamageFromBullet);
    }
  }
}

void Bullet::setSprite()
{
  if (m_ownerObject)
  {
    m_sprite = (m_ownerObject->getType() == GameObjectType_Player)
      ? m_game->getSprite(m_indexOfSpritePlayerBullet)
      : m_game->getSprite(m_indexOfSpriteEnemyBullet);
  }
}