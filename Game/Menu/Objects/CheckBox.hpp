#pragma once

// Include
#include "MenuObject.hpp"

// Class CheckBox
class CheckBox : public MenuObject
{
public:
  explicit CheckBox(const char* name, const Point<int>& point, bool isActive = true);
  void render() override;
  void update() override;
  [[nodiscard]] bool isChecked() const { return m_checked; }

private:
  int m_radius;
  bool m_checked;
};