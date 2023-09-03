#pragma once

// Include
#include "GameObject.hpp"
#include "Human.hpp"

// Class Bonus
class Bonus : public GameObject
{
public:
  enum BonusId
  {
    BonusId_Heart  = 6,
    BonusId_Shield = 7,
    BonusId_Speed  = 8,
    BonusId_Star   = 9
  };

public:
  explicit Bonus(Game* game, const Body& body);
  void render() override;
  void update(int deltaTime) override;
  void giveImprovement(Human& human) const;

private:
  void updateSprite();
  static void giveLife(Human& human);
  static void giveInvulnerability(Human& human);
  static void giveFastSpeed(Human& human);
  static void giveRateOfFire(Human& human);

private:
  const GUI_BITMAP GUI_UNI_PTR* m_pBitmap{};
  BonusId m_bonusId;
  size_t m_indexOfWoodenBox;
};