#pragma once

// Include
#include "Constants.hpp"
#include "Point.hpp"

// Class Joystick
class Joystick
{
public:
  enum TouchID
  {
    TouchID_0 = 0,
    TouchID_1 = 1,
    TouchID_None = 0xFF
  };

  struct GamePad {
    TouchID idJoystick;
    TouchID idField;
    Point<int> touchP[kJoystickMaxNumOfTouches]{};
    Point<float> speedLevel;

    GamePad();
  };

public:
  explicit Joystick();
  void render() const;
  void update();

  [[nodiscard]] GamePad* getGamePad() { return &m_gamePad; }

private:
  void touchProcessing(TouchID id0, TouchID id1, bool* touchField0WasDetected = nullptr);
  void checkTouchOutOfJoystickArea();
  void calculateSpeedLevel();

private:
  GamePad m_gamePad;
  Point<int> m_JoystickP;
  Point<int> m_padP;
  bool m_touchField0WasDetected;
};