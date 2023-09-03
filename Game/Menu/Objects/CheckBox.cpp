// Include
#include "CheckBox.hpp"
#include "Constants.hpp"
#include "ft5336.h"
#include "Point.hpp"

// Global variables
extern TS_StateTypeDef g_tsState;

// Class CheckBox
CheckBox::CheckBox(const char* name, const Point<int>& point, const bool isActive)
  : MenuObject(Type_CheckBox, name, point, isActive)
{
  m_radius = kCheckBoxRadius;
  m_font = &GUI_Font24B_ASCII;
  m_checked = false;
}

void CheckBox::render()
{
  GUI_SetColor(GUI_BLACK);
  GUI_FillCircle(m_center.x, m_center.y, m_radius);
  GUI_SetColor(getColor());
  GUI_FillCircle(m_center.x, m_center.y, m_radius - 2);
  GUI_SetColor(GUI_BLACK);
  if (m_checked)
  {
    GUI_FillCircle(m_center.x, m_center.y, m_radius - 6);
  }
  GUI_SetFont(m_font);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_DispStringHCenterAt(m_name, m_center.x + m_radius + 7 + GUI_GetStringDistX(m_name) / 2, m_center.y - m_radius);
}

void CheckBox::update()
{
  if (isActive())
  {
    if (g_tsState.touchDetected)
    {
      m_touch = { g_tsState.touchX[0], g_tsState.touchY[0] };
    }

    if (m_center.length2(m_touch) <= (m_radius * m_radius))
    {
      setState(State_Selected);
      if (!g_tsState.touchDetected)
      {
        m_touch = { -1, -1 };
        setState(State_Pressed);
        m_checked = !m_checked;
      }
    }
    else
    {
      setState(State_NotPressed);
    }
  }
}