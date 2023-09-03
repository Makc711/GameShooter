#pragma once

// Include
#include "GameObject.hpp"

// Class Block
class Block : public GameObject
{
public:
  explicit Block(Game* game, const Body& body);
  void render() override;

private:
  GUI_COLOR m_color;
};