// Include
#include "PauseMenu.hpp"

// Class PauseMenu
PauseMenu::PauseMenu(Game *game)
{
  m_game = game;
  const Point<int> buttonContinueCenter = {
    LCD_GetXSize() / 2,
    LCD_GetYSize() / 2 + 60
  };
  m_button = new Button(MainMenuItem_Continue, "", buttonContinueCenter);
  m_button->setFont(&GUI_Font24B_ASCII);
  m_id = Id_MainMenu;
}

PauseMenu::~PauseMenu()
{
  delete m_button;
  m_button = nullptr;
}

void PauseMenu::render() const
{
  m_button->render();
}

void PauseMenu::update() const
{
  m_button->update();
  if (m_button->isPressed())
  {
    switch (m_id)
    {
    case Id_MainMenu:
      m_game->setGameState(Game::GameState_Menu);
      m_game->setGameNotInProcess();
      break;
    case Id_NextLevel: 
    case Id_Retry:
      m_game->initialize();
      m_game->setGameState(Game::GameState_Play);
      break;
    }
  }
}

void PauseMenu::setId(const Id id)
{
  m_id = id;
  switch (id)
  {
  case Id_NextLevel: 
    m_button->setName("NEXT LEVEL");
    break;
  case Id_MainMenu: 
    m_button->setName("MAIN MENU");
    break;
  case Id_Retry: 
    m_button->setName("RETRY");
    break;
  }
}