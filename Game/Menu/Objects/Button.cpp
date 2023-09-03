// Include
#include "Button.hpp"
#include "Constants.hpp"
#include "ft5336.h"

// Global variables
extern TS_StateTypeDef g_tsState;

// Class Button
Button::Button(const MainMenuItem id, const char* name, const Point<int>& point, const bool isActive)
  : MenuObject(Type_Button, name, point, isActive)
{
  m_id = id;
  m_width = kButtonWidth;
  m_height = kButtonHeight;
  m_font = &GUI_Font32B_ASCII;
}

void Button::render()
{
  const int x0 = m_center.x - m_width / 2;
  const int y0 = m_center.y - m_height / 2;
  const int x1 = x0 + m_width;
  const int y1 = y0 + m_height;
  GUI_SetColor(GUI_BLACK);
  GUI_FillRoundedRect(x0 - kButtonBorderWidth, y0 - kButtonBorderWidth, 
    x1 + kButtonBorderWidth, y1 + kButtonBorderWidth, kButtonBorderWidth / 2);
  GUI_SetColor(getColor());
  GUI_FillRect(x0, y0, x1, y1);

  GUI_SetColor(GUI_BLACK);
  GUI_SetFont(m_font);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_DispStringHCenterAt(m_name, m_center.x, m_center.y - m_font->YSize / 2);
}

void Button::update()
{
  if (isActive())
  {
    if (g_tsState.touchDetected)
    {
      m_touch = { g_tsState.touchX[0], g_tsState.touchY[0] };
    }

    if ((m_touch.x >= m_center.x - m_width / 2) && (m_touch.x < m_center.x + m_width / 2) &&
      (m_touch.y >= m_center.y - m_height / 2) && (m_touch.y < m_center.y + m_height / 2))
    {
      setState(State_Selected);
      if (!g_tsState.touchDetected)
      {
        m_touch = { -1, -1 };
        setState(State_Pressed);
      }
    }
    else
    {
      setState(State_NotPressed);
    }
  }
}