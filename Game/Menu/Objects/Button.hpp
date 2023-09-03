#pragma once

// Include
#include <sys/_stdint.h>
#include "MainMenuItem.hpp"
#include "MenuObject.hpp"

// Class Button
class Button : public MenuObject
{
public:
  explicit Button(MainMenuItem id, const char* name, const Point<int>& point, bool isActive = true);
  void render() override;
  void update() override;

  [[nodiscard]] MainMenuItem getId() const { return m_id; }

private:
  MainMenuItem m_id;
  uint16_t m_width;
  uint16_t m_height;
};
