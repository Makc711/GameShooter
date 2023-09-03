#pragma once
#include <GUI.h>

// Constants Level
constexpr auto kNumberOfLevels = 10;
constexpr auto kBlocksOnLevelMin = 6;
constexpr auto kBlocksOnLevelMax = 12;
constexpr auto kLevelAttemptsToCreateBlock = 100;
constexpr auto kLevelBlockSizeMax = 80;
constexpr auto kLevelBlockSizeMin = 30;

// Constants Game
constexpr auto kGameObjectsCountMax = 64;
constexpr auto kGameMaxEnemiesOnLevel = 2;
constexpr auto kGameNumberOfSprites = 11;
constexpr auto kGameDelayForMaxFps = 16;
//                                                        1 = BlockJoystick, 1 = Bonus
constexpr auto kGameMaxNumOfObstaclesOnLevel = kBlocksOnLevelMax + kGameMaxEnemiesOnLevel + 1 + 1;

// Constants Joystick
constexpr auto kJoystickPadRadius = 12;
constexpr auto kJoystickRadius = 50;
constexpr auto kJoystickAvailableAreaRadius = kJoystickRadius - kJoystickPadRadius;
constexpr auto kJoystickBorder = 10;
constexpr auto kJoystickColor = GUI_LIGHTGRAY;
constexpr auto kJoystickMaxNumOfTouches = 2;

// Constants Human
constexpr auto kHumanSize = 25;
constexpr auto kHumanGunSize = 6;
constexpr auto kHumanMaxFireDistance = 10000;
constexpr auto kHumanMaxBulletIntersects = 10;

// Constants Enemy
constexpr auto kEnemyStartWait = 2000;
constexpr auto kEnemyTimeFromLastFire = 10000;
constexpr auto kEnemyAreaBorder = kHumanSize * 2;
constexpr auto kEnemyTimeToCheckIntersectWithBlock = 2000;
constexpr auto kEnemyDegreesPerCycle = 10;
constexpr auto kEnemyOffsetAngleToVictoryDance = 2;
constexpr auto kEnemyRechargeTimeToVictoryDance = 300;

// Constants Player
constexpr auto kPlayerSpeed = 0.06f;
constexpr auto kPlayerHealth = 2;
constexpr auto kPlayerRechargeTime = 1500;

// Constants Bullet
constexpr auto kBulletSize = 5;
constexpr auto kBulletSpeed = 0.09f;
constexpr auto kBulletDamageFromBullet = 1;

// Constants Block
constexpr auto kBlockBorderWidth = 2;
constexpr int kBlockBorderToMove = static_cast<int>(kHumanSize * 2.5f / 2.0f);

// Constants Bonus
constexpr auto kBonusHealth = 2;
constexpr auto kBonusIndexOfSpriteWoodenBox = 10;
constexpr auto kBonusGiveHealth = 1;
constexpr auto kBonusGiveInvulnerableTime = 5000;
constexpr auto kBonusGiveFastSpeed = 0.085f;
constexpr auto kBonusGiveRateOfFire = 500;

// Constants MenuConstructor
constexpr auto kMainMenuButtonsCountMax = 6;
constexpr auto kOptionsObjectsCountMax = 2;

// Constants Button
constexpr auto kButtonWidth = 160;
constexpr auto kButtonHeight = 50;
constexpr auto kButtonBorderWidth = 2;
constexpr auto kButtonDistanceBetweenButtonsX = 40;
constexpr auto kButtonDistanceBetweenButtonsY = 30;
constexpr auto kButtonActiveColor = GUI_GREEN;
constexpr auto kButtonPassiveColor = GUI_DARKGRAY;
constexpr auto kButtonSelectedColor = GUI_DARKGREEN;

// Constants CheckBox
constexpr auto kCheckBoxRadius = 12;

// Constants MenuGame
constexpr auto kMenuGameMaxNumOfObstacles = kMainMenuButtonsCountMax + 1;
constexpr auto kMenuGameObjectsCountMax = 32;