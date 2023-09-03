#pragma once

// Include
#include "GameObject.hpp"

// Class Bullet
class Bullet : public GameObject
{
public:
  explicit Bullet(Game* game, const Body& body);
  void render() override;
  void intersect(GameObject* object, Side side) override;
  void setSprite();

  void setOwnerObject(GameObject* object){ m_ownerObject = object; }
  [[nodiscard]] GameObject* getOwnerObject() const { return m_ownerObject; }
  

private:
  GameObject* m_ownerObject;
  IMAGE* m_sprite;
  size_t m_indexOfSpritePlayerBullet;
  size_t m_indexOfSpriteEnemyBullet;
};