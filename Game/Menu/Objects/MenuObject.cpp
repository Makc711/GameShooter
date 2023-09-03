// Include
#include "MenuObject.hpp"
#include "Constants.hpp"

// Class MenuObject
MenuObject::MenuObject(const Type type, const char* name, const Point<int>& point, const bool isActive)
{
  m_type = type;
  m_name = name;
  m_center = point;
  m_state = State_NotPressed;
  m_font = &GUI_Font8_ASCII;
  m_touch = { -1, -1 };
  m_isActive = isActive;
  m_color = m_isActive ? kButtonActiveColor : kButtonPassiveColor;
}

void MenuObject::render()
{

}

void MenuObject::update()
{
  
}

bool MenuObject::isPressed()
{
  bool isPressed = false;
  const State state = m_state;
  if (state == State_Pressed)
  {
    m_state = State_NotPressed;
    isPressed = true;
  }
  return isPressed;
}

void MenuObject::setState(const State state)
{
  if (m_isActive)
  {
    m_state = state;
    updateColor();
  }
}

void MenuObject::setActiveState(const bool isActive)
{
  if (m_isActive != isActive)
  {
    m_isActive = isActive;
    m_color = m_isActive ? kButtonActiveColor : kButtonPassiveColor;
  }
}

void MenuObject::updateColor()
{
  switch (m_state)
  {
  case State_NotPressed:
  case State_Pressed: 
    m_color = kButtonActiveColor;
    break;
  case State_Selected:
    m_color = kButtonSelectedColor;
    break;
  }
}