// Include
#include "Block.hpp"
#include <cstdio>

// Class Block
Block::Block(Game* game, const Body& body)
  : GameObject(game)
{
  m_body = body;
  m_color = GUI_ORANGE;
  m_invulnerable = true;
}

void Block::render()
{
  const Point<int> pointTopLeft = m_body.getTopLeft().cast<int>();
  const Point<int> pointBottomRight = m_body.getBottomRight().cast<int>();
  GUI_SetColor(GUI_BLACK);
  GUI_FillRoundedRect(pointTopLeft.x, pointTopLeft.y, 
    pointBottomRight.x, pointBottomRight.y, kBlockBorderWidth / 2);
  GUI_SetColor(m_color);
  GUI_FillRect(pointTopLeft.x + kBlockBorderWidth, pointTopLeft.y + kBlockBorderWidth, 
    pointBottomRight.x - kBlockBorderWidth, pointBottomRight.y - kBlockBorderWidth);

#ifdef DEBUG
  GUI_SetColor(GUI_BLACK);
  GUI_SetFont(&GUI_Font8_ASCII);
  GUI_SetTextMode(GUI_TM_TRANS);
  char str[6];
  sprintf(str, "%i", pointTopLeft.x);
  GUI_DispStringAt(str, pointTopLeft.x + 3, pointTopLeft.y + 3);
  GUI_SetColor(GUI_RED);
  sprintf(str, "%i", pointTopLeft.y);
  GUI_DispStringAt(str, pointTopLeft.x + 3, pointTopLeft.y + 11);
#endif
}