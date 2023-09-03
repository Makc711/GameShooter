#pragma once

// Include
#include <GUI.h>
#include "Point.hpp"

// class MenuObject
class MenuObject
{
public:
  enum Type
  {
    Type_Button,
    Type_CheckBox
  };

protected:
  enum State
  {
    State_NotPressed,
    State_Selected,
    State_Pressed
  };

public:
  explicit MenuObject(Type type, const char* name, const Point<int>& point, bool isActive);
  virtual ~MenuObject() = default;
  virtual void render();
  virtual void update();
  [[nodiscard]] bool isPressed();
  void setName(const char* name) { m_name = name; }
  void setState(State state);
  [[nodiscard]] State getState() const { return m_state; }
  void setActiveState(bool isActive);
  [[nodiscard]] GUI_COLOR getColor() const { return m_color; }
  [[nodiscard]] bool isActive() const { return m_isActive; }
  void setFont(GUI_CONST_STORAGE GUI_FONT* font) { m_font = font; }
  [[nodiscard]] Type getType() const { return m_type; }

private:
  void updateColor();

protected:  
  const char* m_name;
  Point<int> m_center;
  GUI_CONST_STORAGE GUI_FONT* m_font;
  Point<int> m_touch;

private:
  Type m_type;
  bool m_isActive{};
  State m_state;
  GUI_COLOR m_color{};
};
