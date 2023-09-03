// Include
#include "Player.hpp"
#include "Bonus.hpp"

// Class Player
Player::Player(Game* game, const Body& body)
  : Human(game)
{
  m_body = body;
  m_speed = kPlayerSpeed;
  m_health = kPlayerHealth;
  m_rechargeTime = kPlayerRechargeTime;

  m_distanceToEnemy = 0;
  m_gamePad = m_game->getJoystick()->getGamePad();
  m_indexOfSpriteDamaged = m_game->findIndexOfSprite(&bmPlayerDamaged);
  m_indexOfSprite = m_game->findIndexOfSprite(&bmPlayer);
  updateSprite();
}

void Player::update(const int deltaTime)
{
  Human::update(deltaTime);

  if (m_gamePad->idField != Joystick::TouchID_None)
  {
    const Point<float> touchPoint = m_gamePad->touchP[m_gamePad->idField].cast<float>();
    m_angle = calculateAngle(m_body.getCenter(), touchPoint);

    if (fire())
    {
      const Point<float> gunPoint = calculateFrontCellPosition();
      const Point<float> direction = (gunPoint - m_body.getCenter()).normalize();
      m_game->pushBodiesToList();
      
#ifdef DEBUG
      Array<Point<float>, kHumanMaxBulletIntersects> bulletIntersects;
      m_distanceToEnemy = distanceToHuman(gunPoint, direction, GameObjectType_Enemy, bulletIntersects);
#else
      m_distanceToEnemy = distanceToHuman(gunPoint, direction, GameObjectType_Enemy);
#endif

      m_game->deleteLastBodiesFromList();
    }
  }

  move(m_gamePad->speedLevel);
}