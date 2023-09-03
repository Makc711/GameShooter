// Include
#include "Bonus.hpp"

// Class Bonus
Bonus::Bonus(Game* game, const Body& body)
  : GameObject(game)
{
  m_body = body;
  m_health = kBonusHealth;

  m_bonusId = static_cast<BonusId>(Level::getRandom(BonusId_Heart, BonusId_Star));
  m_indexOfWoodenBox = m_game->findIndexOfSprite(&bmWoodenBox);
  updateSprite();
}

void Bonus::render()
{
  const auto point = m_body.getTopLeft();
  GUI_DrawBitmap(m_pBitmap, static_cast<int>(point.x), static_cast<int>(point.y));
}

void Bonus::update(const int deltaTime)
{
  GameObject::update(deltaTime);
  updateSprite();
}

void Bonus::updateSprite()
{
  m_pBitmap = (m_health == 1)
            ? m_game->getSprite(m_bonusId)->pBitmap
            : m_game->getSprite(m_indexOfWoodenBox)->pBitmap;
}

void Bonus::giveImprovement(Human& human) const
{
  switch (m_bonusId)
  {
  case BonusId_Heart: 
    giveLife(human);
    break;
  case BonusId_Shield: 
    giveInvulnerability(human);
    break;
  case BonusId_Speed: 
    giveFastSpeed(human);
    break;
  case BonusId_Star: 
    giveRateOfFire(human);
    break;
  }
}

void Bonus::giveLife(Human& human)
{
  human.setHealth(human.getHealth() + kBonusGiveHealth);
}

void Bonus::giveInvulnerability(Human& human)
{
  human.setInvulnerable(true);
  human.setInvulnerableTime(kBonusGiveInvulnerableTime);
}

void Bonus::giveFastSpeed(Human& human)
{
  human.setSpeed(kBonusGiveFastSpeed);
}

void Bonus::giveRateOfFire(Human& human)
{
  human.setRechargeTime(kBonusGiveRateOfFire);
}