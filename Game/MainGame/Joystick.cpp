// Include
#include "Joystick.hpp"
#include <cmath>
#include <cstdio>
#include "ft5336.h"

// Global variables
extern TS_StateTypeDef g_tsState;

// Class Joystick
Joystick::GamePad::GamePad()
{
  idJoystick = TouchID_None;
  idField = TouchID_None;
  speedLevel = Point<float>();
  for (auto& i : touchP)
  {
    i = Point<int>();
  }
}

Joystick::Joystick()
{
  m_gamePad = GamePad();
  m_JoystickP = Point<int>(kJoystickRadius + kJoystickBorder, LCD_GetYSize() - kJoystickRadius - 1 - kJoystickBorder);
  m_padP = m_JoystickP;
  m_touchField0WasDetected = false;
}

void Joystick::render() const
{
  GUI_SetColor(kJoystickColor);
  GUI_DrawCircle(m_JoystickP.x, m_JoystickP.y, kJoystickRadius);
  GUI_DrawCircle(m_padP.x, m_padP.y, kJoystickPadRadius);
}

void Joystick::update()
{
  if (g_tsState.touchDetected)
  {
    touchProcessing(TouchID_1, TouchID_0);

    if (g_tsState.touchDetected > 1)
    {
      touchProcessing(TouchID_0, TouchID_1, &m_touchField0WasDetected);
    }
    else
    {
      if (m_gamePad.idField == TouchID_1)
      {
        m_gamePad.idField = TouchID_None;
      }
      if (m_gamePad.idJoystick == TouchID_1)
      {
        if (m_gamePad.idField == TouchID_0)
        {
          m_touchField0WasDetected = true;
          m_gamePad.idField = TouchID_None;
        }
        m_gamePad.idJoystick = TouchID_0;
      }
    }

    checkTouchOutOfJoystickArea();
  }
  else
  {
    m_touchField0WasDetected = false;
    m_gamePad.idJoystick = TouchID_None;
    m_gamePad.idField = TouchID_None;
  }

  if (m_gamePad.idJoystick != TouchID_None)
  {
    float sinA = 0.0f;
    float cosA = 0.0f;
    Point<int>::calculateSinCos(sinA, cosA, m_JoystickP, m_gamePad.touchP[m_gamePad.idJoystick]);

    if (m_gamePad.touchP[m_gamePad.idJoystick].length2(m_JoystickP) <= 
      (kJoystickAvailableAreaRadius * kJoystickAvailableAreaRadius))
    {
      m_padP = m_gamePad.touchP[m_gamePad.idJoystick];
    }
    else
    {
      m_padP.x = m_JoystickP.x + static_cast<int>(kJoystickAvailableAreaRadius * cosA);
      m_padP.y = m_JoystickP.y + static_cast<int>(kJoystickAvailableAreaRadius * sinA);
    }

    calculateSpeedLevel();
  }
  else
  {
    m_padP = m_JoystickP;
    m_gamePad.speedLevel.x = 0;
    m_gamePad.speedLevel.y = 0;
  }

#ifdef DEBUG
  GUI_SetColor(GUI_BLACK);
  GUI_SetFont(&GUI_Font8_ASCII);
  GUI_SetTextMode(GUI_TM_TRANS);
  char str[17];
  sprintf(str, "Speed:(%i; %i)", static_cast<int8_t>(m_gamePad.speedLevel.x * 100), static_cast<int8_t>(m_gamePad.speedLevel.y * 100));
  GUI_DispStringAt(str, 5, 18);
#endif
}

void Joystick::touchProcessing(const TouchID id0, const TouchID id1, bool* touchField0WasDetected)
{
  const auto touchTmp = Point<int>(g_tsState.touchX[id1], g_tsState.touchY[id1]);
  if (touchTmp.length2(m_JoystickP) <= (kJoystickRadius * kJoystickRadius))
  {
    if (m_gamePad.idJoystick == id0)
    {
      m_gamePad.idField = id1;
      m_gamePad.touchP[m_gamePad.idField] = touchTmp;
      if ((touchField0WasDetected != nullptr) && (*touchField0WasDetected))
      {
        *touchField0WasDetected = false;
        m_gamePad.idField = id0;
        m_gamePad.idJoystick = id1;
      }
    }
    else
    {
      if (m_gamePad.idField == id1)
      {
        m_gamePad.idField = TouchID_None;
      }
      m_gamePad.idJoystick = id1;
      m_gamePad.touchP[m_gamePad.idJoystick] = touchTmp;
    }
  }
  else
  {
    if ((touchField0WasDetected != nullptr) && (*touchField0WasDetected))
    {
      *touchField0WasDetected = false;
      m_gamePad.idField = TouchID_0;
      m_gamePad.idJoystick = TouchID_1;
    }
    if (m_gamePad.idJoystick == id1)
    {
      m_gamePad.touchP[m_gamePad.idJoystick] = touchTmp;
    }
    else
    {
      if (m_gamePad.idField != id0)
      {
        if (m_gamePad.idJoystick == id1)
        {
          m_gamePad.idJoystick = TouchID_None;
        }
        m_gamePad.idField = id1;
        m_gamePad.touchP[m_gamePad.idField] = touchTmp;
      }
    }
  }
}

void Joystick::checkTouchOutOfJoystickArea()
{
  if ((m_gamePad.idJoystick != TouchID_None) &&
      (m_gamePad.touchP[m_gamePad.idJoystick].length2(m_JoystickP) > 
      (kJoystickRadius * kJoystickRadius * 4)))
  {
    m_touchField0WasDetected = false;
    m_gamePad.idJoystick = TouchID_None;
  }
}

void Joystick::calculateSpeedLevel()
{
  const auto delta = m_padP - m_JoystickP;
  m_gamePad.speedLevel = delta.cast<float>() / kJoystickAvailableAreaRadius;
  const float sumXY = std::abs(m_gamePad.speedLevel.x) + std::abs(m_gamePad.speedLevel.y);
  if (sumXY != 0.0f)
  {
    const float k = 1.0f / sumXY;
    m_gamePad.speedLevel.x *= k;
    m_gamePad.speedLevel.y *= k;
  }
}
