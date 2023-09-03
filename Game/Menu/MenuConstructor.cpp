// Include
#include "MenuConstructor.hpp"
#include <cstring>
#include "CheckBox.hpp"
#include "fatfs.h"

// Class MenuConstructor
MenuConstructor::MenuConstructor(Game* game)
{
  m_game = game;
  m_menuState = MenuState_MainMenu;
  createMenuObjects();
  const Point<int> buttonBackCenter = { LCD_GetXSize() / 2, LCD_GetYSize() - kButtonHeight / 2 - 15 };
  m_buttonAboutBack = new Button(MainMenuItem_About, "BACK", buttonBackCenter);
  m_isSdCardDetected = false;
  m_isSaveCreated = false;
}

MenuConstructor::~MenuConstructor()
{
  m_mainMenuObjects.deleteAllObjects();
  m_optionsObjects.deleteAllObjects();
}

void MenuConstructor::createMenuObjects()
{
  const Point<int> buttonNewGameCenter = {
    (LCD_GetXSize() - kButtonDistanceBetweenButtonsX - kButtonWidth) / 2,
    LCD_GetYSize() / 2 - kButtonDistanceBetweenButtonsY - kButtonHeight };
  const auto buttonNewGame = new Button(MainMenuItem_NewGame, "NEW GAME", buttonNewGameCenter);
  m_mainMenuObjects.pushBack(buttonNewGame);

  const Point<int> buttonContinueCenter = {
    buttonNewGameCenter.x + kButtonDistanceBetweenButtonsX + kButtonWidth,
    buttonNewGameCenter.y
  };
  const auto buttonContinue = new Button(MainMenuItem_Continue, "CONTINUE", buttonContinueCenter, false);
  m_mainMenuObjects.pushBack(buttonContinue);

  const Point<int> buttonSaveCenter = {
    buttonNewGameCenter.x,
    buttonNewGameCenter.y + kButtonDistanceBetweenButtonsY + kButtonHeight
  };
  const auto buttonSave = new Button(MainMenuItem_Save, "SAVE", buttonSaveCenter, false);
  m_mainMenuObjects.pushBack(buttonSave);

  const Point<int> buttonLoadCenter = {
    buttonContinueCenter.x,
    buttonSaveCenter.y
  };
  const auto buttonLoad = new Button(MainMenuItem_Load, "LOAD", buttonLoadCenter, false);
  m_mainMenuObjects.pushBack(buttonLoad);

  const Point<int> buttonOptionsCenter = {
    buttonNewGameCenter.x,
    buttonSaveCenter.y + kButtonDistanceBetweenButtonsY + kButtonHeight
  };
  const auto buttonOptions = new Button(MainMenuItem_Options, "OPTIONS", buttonOptionsCenter);
  m_mainMenuObjects.pushBack(buttonOptions);

  const Point<int> buttonAboutCenter = {
    buttonContinueCenter.x,
    buttonOptionsCenter.y
  };
  const auto buttonAbout = new Button(MainMenuItem_About, "ABOUT", buttonAboutCenter);
  m_mainMenuObjects.pushBack(buttonAbout);

  const Point<int> checkBoxShowFpsCenter = { 40 + kCheckBoxRadius, 100 };
  const auto checkBoxShowFps = new CheckBox("Show FPS", checkBoxShowFpsCenter);
  m_optionsObjects.pushBack(checkBoxShowFps);

  const Point<int> buttonBackCenter = { 40 + kButtonWidth / 2, 200 };
  const auto buttonBack = new Button(MainMenuItem_Options, "BACK", buttonBackCenter);
  m_optionsObjects.pushBack(buttonBack);
}

void MenuConstructor::checkFlashCard()
{
  if (BSP_SD_IsDetected() == SD_PRESENT)
  {
    if (FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
    {
      FRESULT res = f_mount(&SDFatFS, static_cast<const TCHAR*>(SDPath), 1);
      if (res == FR_OK)
      {
        m_isSdCardDetected = true;
        FILINFO fileInfo;
        res = f_stat(m_nameOfFileSave, &fileInfo);
        m_isSaveCreated = (res == FR_OK) && (fileInfo.fsize != 0);
      }
      else
      {
        m_isSdCardDetected = false;
      }
    }
  }
  else
  {
    if (FATFS_UnLinkDriver(SDPath) == 0)
    {
      m_isSaveCreated = false;
      m_isSdCardDetected = false;
      f_mount(nullptr, static_cast<const TCHAR*>(SDPath), 0);
    }
  }
}

void MenuConstructor::loadSavedGame()
{
  if (m_isSdCardDetected)
  {
    if (m_isSaveCreated && (f_open(&SDFile, m_nameOfFileSave, FA_READ) == FR_OK))
    {
      constexpr size_t sizeOfData = sizeof(GameDataToSave);
      size_t readBytesNumber;
      FRESULT res = f_read(&SDFile, &m_gameData, sizeOfData, &readBytesNumber);
      if ((res == FR_OK) && (readBytesNumber == sizeOfData))
      {
        loadGameData();
      }
      else
      {
        m_isSaveCreated = false;
      }
      res = f_close(&SDFile);
    }
    else
    {
      m_isSaveCreated = false;
    }
  }
}

void MenuConstructor::loadGameData()
{
  m_game->shutdown();
  m_game->setPlayerPoints(m_gameData.playerPoints);
  m_game->setEnemyPoints(m_gameData.enemyPoints);
  m_game->setPlayerDiedState(m_gameData.isPlayerDied);
  m_game->setEnemiesDiedState(m_gameData.isEnemiesDied);

  for (size_t i = 0; i < m_gameData.levelBodies.count(); i++)
  {
    if ((m_gameData.levelBodies[i].getType() == GameObjectType_Player) 
      && m_gameData.isPlayerDied)
    {
      m_gameData.levelBodies.deleteObject(i);
    }
    if ((m_gameData.levelBodies[i].getType() == GameObjectType_Enemy) 
      && m_gameData.isEnemiesDied)
    {
      m_gameData.levelBodies.deleteObject(i);
    }
  }
  const auto level = new Level(m_game);
  m_game->setLevel(level);
  level->createLevelObjectsFromBodies(m_gameData.levelBodies, m_gameData.playerPoints);
  m_game->pushBlocksBodiesToList();
}

void MenuConstructor::saveGameData()
{
  if (m_isSdCardDetected)
  {
    f_unlink(m_nameOfFileSave);
    FRESULT res = f_open(&SDFile, m_nameOfFileSave, FA_CREATE_ALWAYS | FA_WRITE);
    if (res == FR_OK)
    {
      createGameData();
      constexpr size_t sizeOfData = sizeof(GameDataToSave);
      size_t bytesWritten;
      res = f_write(&SDFile, &m_gameData, sizeOfData, &bytesWritten);
      m_isSaveCreated = (bytesWritten == sizeOfData) && (res == FR_OK);

      res = f_close(&SDFile);
      if ((res == FR_OK) && !m_isSaveCreated)
      {
        res = f_unlink(m_nameOfFileSave);
      }
    }
    else
    {
      m_isSaveCreated = false;
    }
  }
}

void MenuConstructor::createGameData()
{
  m_gameData.playerPoints = m_game->getPlayerPoints();
  m_gameData.enemyPoints = m_game->getEnemyPoints();
  m_gameData.isPlayerDied = m_game->isPlayerDied();
  m_gameData.isEnemiesDied = m_game->isEnemiesDied();
}

void MenuConstructor::setGameBodies()
{
  m_gameData.levelBodies.deleteLastFrom(0);
  const Array<GameObject*, kGameObjectsCountMax> objects = m_game->getObjects();
  for (const auto& gameObject : objects)
  {
    if (gameObject)
    {
      m_gameData.levelBodies.pushBack(gameObject->getBody());
    }
  }
}

void MenuConstructor::render() const
{
  switch (m_menuState)
  {
  case MenuState_MainMenu:
    renderMainMenu();
    break;
  case MenuState_Options: 
    renderOptions();
    break;
  case MenuState_About: 
    renderAbout();
    break;
  }
}

void MenuConstructor::renderMainMenu() const
{
  for (const auto& object : m_mainMenuObjects)
  {
    if (object)
    {
      object->render();
    }
  }
}

void MenuConstructor::renderOptions() const
{
  for (const auto& object : m_optionsObjects)
  {
    if (object)
    {
      object->render();
    }
  }
}

void MenuConstructor::renderAbout() const
{
  constexpr int startPosX = 15;
  int posY = 15;
  GUI_SetColor(GUI_BLACK);
  GUI_SetFont(&GUI_Font16B_ASCII);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_DispStringAt("Author: Maxim Rusanov (maxim.rusanof@gmail.com)", startPosX, posY);
  posY += GUI_Font16B_ASCII.YSize * 2;
  GUI_SetFont(&GUI_Font16_ASCII);
  GUI_DispStringAt("Rules of the game:", startPosX, posY);
  posY += GUI_Font16_ASCII.YSize;
  GUI_DispStringAt("1. The game lasts up to 10 points.", startPosX, posY);
  posY += GUI_Font16_ASCII.YSize;
  GUI_DispStringAt("2. Each level increases the difficulty of the game.", startPosX, posY);
  posY += GUI_Font16_ASCII.YSize;
  GUI_DispStringAt("3. There are bonuses on the playing field, collecting which you can improve", startPosX, posY);
  posY += GUI_Font16_ASCII.YSize;
  GUI_DispStringAt("the characteristics of the player.", startPosX, posY);
  m_buttonAboutBack->render();
}

void MenuConstructor::update()
{
  switch (m_menuState)
  {
  case MenuState_MainMenu:
    updateMainMenu();
    break;
  case MenuState_Options: 
    updateOptions();
    break;
  case MenuState_About: 
    updateAbout();
    break;
  }
}

void MenuConstructor::updateMainMenu()
{
  checkFlashCard();

  for (const auto& object : m_mainMenuObjects)
  {
    if (object)
    {
      object->update();
      if (const auto button = dynamic_cast<Button*>(object))
      {
        updateButtonActiveState(button);
        if (button->isPressed())
        {
          switch (button->getId())
          {
          case MainMenuItem_NewGame:
            m_game->resetGameProgress();
            m_game->initialize();
            m_game->setGameState(Game::GameState_Play);
            break;
          case MainMenuItem_Continue: 
            m_game->returnToPreviousState();
            break;
          case MainMenuItem_Save: 
            saveGameData();
            break;
          case MainMenuItem_Load: 
            loadSavedGame();
            if (m_isSaveCreated)
            {
              m_game->setGameState(Game::GameState_Play);
            }
            break;
          case MainMenuItem_Options: 
            m_menuState = MenuState_Options;
            break;
          case MainMenuItem_About: 
            m_menuState = MenuState_About;
            break;
          }
        }
      }
    }
  }
}

void MenuConstructor::updateButtonActiveState(Button* button) const
{
  const MainMenuItem buttonId = button->getId();
  if (buttonId == MainMenuItem_Continue)
  {
    button->setActiveState(m_game->isGameInProcess());
  }
  else if (buttonId == MainMenuItem_Save)
  {
    const bool isGameInProcess = m_game->isGameInProcess()
                                && m_game->getPlayerPoints() < kNumberOfLevels
                                && m_game->getEnemyPoints() < kNumberOfLevels;
    button->setActiveState(m_isSdCardDetected && isGameInProcess);
  }
  else if (buttonId == MainMenuItem_Load)
  {
    button->setActiveState(m_isSdCardDetected && m_isSaveCreated);
  }
}

void MenuConstructor::updateOptions()
{
  for (const auto& object : m_optionsObjects)
  {
    if (object)
    {
      object->update();
      if (object->getType() == MenuObject::Type_Button)
      {
        const auto buttonBack = dynamic_cast<Button*>(object);
        if (buttonBack->isPressed())
        {
          m_menuState = MenuState_MainMenu;
        }
      }

      if (object->getType() == MenuObject::Type_CheckBox)
      {
        const auto checkBoxShowFps = dynamic_cast<CheckBox*>(object);
        m_game->setPrintFps(checkBoxShowFps->isChecked());
      }
    }
  }
}

void MenuConstructor::updateAbout()
{
  m_buttonAboutBack->update();
  if (m_buttonAboutBack->isPressed())
  {
    m_menuState = MenuState_MainMenu;
  }
}