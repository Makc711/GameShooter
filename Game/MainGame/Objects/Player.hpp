#pragma once

// Include
#include "Human.hpp"
#include "Joystick.hpp"

// Class Player
class Player final : public Human
{
public:
  explicit Player(Game* game, const Body& body);
  void update(int deltaTime) override;

  float getDistanceToEnemy()
  {
    const float distance = m_distanceToEnemy;
    m_distanceToEnemy = 0.0f;
    return distance;
  }

private:
  float m_distanceToEnemy;
  Joystick::GamePad* m_gamePad;
};