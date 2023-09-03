#pragma once

enum GameObjectType
{
  GameObjectType_None,
  GameObjectType_Block,
  GameObjectType_Player,
  GameObjectType_Enemy,
  GameObjectType_Bullet,
  GameObjectType_Bonus,
  GameObjectType_BlockJoystick
};

enum Side
{
  Side_Left,
  Side_Right,
  Side_Top,
  Side_Bottom,
  Side_None
};