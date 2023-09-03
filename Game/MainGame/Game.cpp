#include "Game.hpp"
#include <cmath>
#include <cstdio>
#include "cmsis_gcc.h"
#include "main.h"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Block.hpp"
#include "Bonus.hpp"
#include "Bullet.hpp"
#include "Level.hpp"

// Class Game
Game::Game()
{
  m_isGameActive = true;
  m_player = nullptr;
  m_playerPoints = 0;
  m_enemyPoints = 0;
  m_isPlayerDied = false;
  m_isEnemiesDied = false;
  m_gameState = GameState_Menu;
  m_previousGameState = GameState_Menu;
  m_menuConstructor = new MenuConstructor(this);
  m_pauseMenu =  new PauseMenu(this);
  m_level = nullptr;
  m_joystick = new Joystick();
  m_timeLastFrame = GUI_GetTime();
  m_blocksCount = 0;
  m_isGameInProcess = false;
  m_isPrintFps = false;

  m_hDst = 0;
  m_hLCD = 0;
}

Game::~Game()
{
  for (const auto& image : m_sprites)
  {
    if (image.hMem)
    {
      GUI_MEMDEV_Delete(image.hMem);
    }
  }

  delete m_menuConstructor;
  m_menuConstructor = nullptr;

  delete m_pauseMenu;
  m_pauseMenu = nullptr;

  delete m_level;
  m_level = nullptr;

  delete m_joystick;
  m_joystick = nullptr;

  if (m_hLCD)
  {
    GUI_MEMDEV_Delete(m_hLCD);
  }
  if (m_hDst)
  {
    GUI_MEMDEV_Delete(m_hDst);
  }
}

void Game::pushBlocksBodiesToList()
{
  for (const auto& gameObject : m_objects)
  {
    if (gameObject && gameObject->getType() == GameObjectType_Block)
    {
      auto objectBody = gameObject->getBody();
      objectBody.addBorder(static_cast<float>(kBulletSize) / 2.0f);
      m_levelBodies.pushBack(objectBody);
    }
  }
  m_blocksCount = m_levelBodies.count();
}

void Game::pushBodiesToList()
{
  for (const auto& gameObject : m_objects)
  {
    if (gameObject)
    {
      auto body = gameObject->getBody();
      const auto type = body.getType();
      if ((type != GameObjectType_Block) && 
        (type != GameObjectType_Bullet))
      {
        if ((type == GameObjectType_Enemy) || 
          (type == GameObjectType_Bonus))
        {
          body.addBorder(static_cast<float>(kBulletSize) / 2.0f);
        }
        m_levelBodies.pushBack(body);
      }
    }
  }
}

void Game::deleteLastBodiesFromList()
{
  m_levelBodies.deleteLastFrom(m_blocksCount);
}

void Game::setupSystem()
{
  loadTextures();
  prepareDisplayForDrawing();
}

void Game::loadTextures()
{
  for (auto& image : m_sprites)
  {
    getImage(image);
  }
}

/**
  * @brief  Create the pictures memdev and draw them inside
  * @param  pImage : pointer to the pictures structure
  * @retval 1 - ERROR, 0 - OK
  */
int Game::getImage(IMAGE &pImage) 
{
  /* Get the picture sizes */
  pImage.width = pImage.pBitmap->XSize;
  pImage.height = pImage.pBitmap->YSize;
  /* Allocate the needed memdev pictures */
  pImage.hMem  = GUI_MEMDEV_CreateFixed(
                0, 
                0, 
                pImage.width, 
                pImage.height, 
                GUI_MEMDEV_NOTRANS, 
                GUI_MEMDEV_APILIST_32, 
                GUICC_M8888I);
  /* Exit if any issue occurred on the memdev creation */
  if (pImage.hMem == 0) 
  {
    return 1;
  }
  /* Select the memdev created and paint the picture on it */
  GUI_MEMDEV_Select(pImage.hMem);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_Clear();
  GUI_DrawBitmap(pImage.pBitmap, 0, 0);
  /* Select the display after finishing the job */
  GUI_MEMDEV_Select(0);
  return 0;
}

void Game::initialize()
{
  delete m_level;
  m_level = new Level(this);
  m_level->createLevelObjects();
  m_menuConstructor->setGameBodies();
  pushBlocksBodiesToList();
  m_isPlayerDied = false;
  m_isEnemiesDied = false;
}

void Game::setLevel(Level* level)
{
  delete m_level;
  m_level = level;
}

bool Game::loop()
{
  const GUI_TIMER_TIME timeContinue = GUI_GetTime() + kGameDelayForMaxFps;
  const int deltaTime = timeBetweenFrames();

  GUI_MEMDEV_Select(m_hDst);
  GUI_MEMDEV_Write(m_hLCD);

  switch (m_gameState)
  {
  case GameState_Menu:
    if (m_isGameInProcess && m_menuConstructor->isStateMainMenu())
    {
      render();
    }
    m_menuConstructor->render();
    m_menuConstructor->update();
    break;
  case GameState_Play:
    render();
    if (isPauseButtonPressed())
    {
      break;
    }
    update(deltaTime);
    break;
  case GameState_Pause:
    render();
    m_pauseMenu->render();
    if (isPauseButtonPressed())
    {
      break;
    }
    if (m_isPlayerDied)
    {
      update(deltaTime);
    }
    m_pauseMenu->update();
    break;
  }

  if (m_isPrintFps)
  {
    printFPS(deltaTime);
  }

  GUI_MEMDEV_Select(0);
  GUI_MEMDEV_CopyToLCD(m_hDst);

  /* Add some delay to achieve minimum timing */
  const GUI_TIMER_TIME timeNow = GUI_GetTime();
  if (timeContinue > timeNow) 
  {
    GUI_Delay(timeContinue - timeNow);
  }
  else
  {
    GUI_Exec();
  }

  return m_isGameActive;
}

void Game::printFPS(const int deltaTime)
{
  GUI_SetColor(GUI_BLACK);
  GUI_SetFont(&GUI_Font8_ASCII);
  GUI_SetTextMode(GUI_TM_TRANS);
  const int fps = (deltaTime != 0) ? (1000 / deltaTime) : (1000 / kGameDelayForMaxFps);
  char str[3];
  sprintf(str, "%d", fps);
  GUI_DispStringAt(str, 5, 5);
}

void Game::shutdown()
{
  m_objects.deleteAllObjects();
  m_levelBodies.deleteLastFrom(0);
  m_player = nullptr;
  m_enemies.deleteLastFrom(0);
}

int Game::timeBetweenFrames()
{
  const int time = GUI_GetTime();
  const int deltaTime = time - m_timeLastFrame;
  m_timeLastFrame = time;
  return deltaTime;
}

void Game::render() const
{
  for (const auto& object : m_objects)
  {
    if (object)
    {
      object->render();
    }
  }
  m_joystick->render();
  drawText();
}

void Game::drawText() const
{
  GUI_SetColor(GUI_GREEN);
  GUI_SetFont(&GUI_Font16B_ASCII);
  GUI_SetTextMode(GUI_TM_TRANS);
  char str[4];
  sprintf(str, "%2d ", m_playerPoints);
  const int strWidth = GUI_GetStringDistX(str);
  const auto centerX = static_cast<int16_t>(LCD_GetXSize() / 2);
  GUI_DispStringAt(str, centerX - strWidth, 5);
  GUI_SetColor(GUI_BLACK);
  GUI_DispCharAt(':', centerX, 4);
  const int charWidth = GUI_GetCharDistX(':');
  GUI_SetColor(GUI_RED);
  sprintf(str, " %d", m_enemyPoints);
  GUI_DispStringAt(str, centerX + charWidth, 5);
  const int centerY = LCD_GetYSize() / 2;

  if (m_isPlayerDied)
  {
    GUI_SetColor(GUI_RED);
    GUI_SetFont(&GUI_Font24B_ASCII);
    constexpr char strPlayerDied[] = "Player died!";
    const int strPlayerDiedWidth = GUI_GetStringDistX(strPlayerDied);
    GUI_DispStringAt(strPlayerDied, centerX - strPlayerDiedWidth / 2, centerY - GUI_Font24B_ASCII.YSize * 4);
  }

  if (m_isEnemiesDied)
  {
    GUI_SetColor(GUI_GREEN);
    GUI_SetFont(&GUI_Font24B_ASCII);
    constexpr char strEnemiesDied[] = "Enemies died!";
    const int strEnemiesDiedWidth = GUI_GetStringDistX(strEnemiesDied);
    GUI_DispStringAt(strEnemiesDied, centerX - strEnemiesDiedWidth / 2, centerY - GUI_Font24B_ASCII.YSize * 3);
  }

  if (m_playerPoints >= kNumberOfLevels)
  {
    GUI_SetColor(GUI_GREEN);
    GUI_SetFont(&GUI_Font24B_ASCII);
    constexpr char strWin[] = "YOU ARE WIN!!!";
    const int strWinWidth = GUI_GetStringDistX(strWin);
    GUI_DispStringAt(strWin, centerX - strWinWidth / 2, centerY - GUI_Font24B_ASCII.YSize);
  }
  else if (m_enemyPoints >= kNumberOfLevels)
  {
    GUI_SetColor(GUI_RED);
    GUI_SetFont(&GUI_Font24B_ASCII);
    constexpr char strLoose[] = "YOU ARE LOOSE...";
    const int strLooseWidth = GUI_GetStringDistX(strLoose);
    GUI_DispStringAt(strLoose, centerX - strLooseWidth / 2, centerY - GUI_Font24B_ASCII.YSize);
  }
}

int Game::prepareDisplayForDrawing()
{
  /* Get the respective width and height of the screen */
  const int xSize = LCD_GetXSize();
  const int ySize = LCD_GetYSize();

  /* Create the LCD memory devices if not existant */
  if (m_hLCD == 0) 
  {
    m_hLCD = GUI_MEMDEV_CreateFixed(0, 0, xSize, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, GUICC_M8888I);
    /* Exit if any issue when creating the memdev */
    if (m_hLCD == 0)
    {
      return 1;
    }
    /* Initialise the memdev with what's displayed */
    GUI_MEMDEV_CopyFromLCD(m_hLCD);
  }  
  /* Create the Destination memory devices if not existant */
  if (m_hDst == 0)
  {
    /* Exit if any issue when creating the memdev */
    m_hDst = GUI_MEMDEV_CreateFixed(0, 0, xSize, ySize, GUI_MEMDEV_NOTRANS, GUI_MEMDEV_APILIST_32, GUICC_M8888I);
    if (m_hDst == 0) 
    {
      return 2;
    }
  }
  return 0;
}

bool Game::isPauseButtonPressed()
{
  if (HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin) == GPIO_PIN_SET)
  {
    m_isGameInProcess = true;
    m_previousGameState = m_gameState;
    m_gameState = GameState_Menu;
    return true;
  }
  return false;
}

void Game::update(const int deltaTime)
{
  m_joystick->update();

  for (auto& object : m_objects)
  {
    if (object && (object->getType() != GameObjectType_Block))
    {
      object->update(deltaTime);

      if (object->getHealth() <= 0) 
      {
        if (object == m_player)
        {
          m_player = nullptr;
        }

        for (size_t i = 0; i < m_enemies.count(); i++)
        {
          if (object == m_enemies[i])
          {
            m_enemies[i] = nullptr;
          }
        }

        m_objects.deleteObject(object);
      }
    }
  }

  if (!m_player && !m_isPlayerDied)
  {
    m_enemyPoints++;
    m_isPlayerDied = true;
  }

  if (m_enemyPoints < kNumberOfLevels)
  {
    size_t numberOfAliveEnemies = m_enemies.count();
    for (size_t i = 0; i < m_enemies.count(); i++)
    {
      if (m_enemies[i] == nullptr)
      {
        numberOfAliveEnemies--;
      }
    }
    if ((numberOfAliveEnemies == 0) && !m_isEnemiesDied)
    {
      m_playerPoints++;
      m_isEnemiesDied = true;
    }
  }

  if (m_isPlayerDied || m_isEnemiesDied)
  {
    if (m_joystick->getGamePad()->idField == Joystick::TouchID_None)
    {
      if ((m_playerPoints >= kNumberOfLevels) || (m_enemyPoints >= kNumberOfLevels))
      {
        m_pauseMenu->setId(PauseMenu::Id_MainMenu);
      }
      else
      {
        m_pauseMenu->setId((m_isPlayerDied && !m_isEnemiesDied)
          ? PauseMenu::Id_Retry
          : PauseMenu::Id_NextLevel);
      }
      m_gameState = GameState_Pause;
    }
  }
}

void Game::resetGameProgress()
{
  m_playerPoints = 0;
  m_enemyPoints = 0;
}

GameObject* Game::createObject(const Body& body)
{
  GameObject* object = nullptr;
  switch (body.getType())
  {
  case GameObjectType_BlockJoystick:
    object = new Block(this, body);
    object->setType(GameObjectType_Block);
    break;
  case GameObjectType_Block:
    {
      const Point<float> newPoint = body.getTopLeft() - kBlockBorderToMove;
      object = new Block(this, { 
        newPoint,
        body.getSize() + kBlockBorderToMove * 2,
        body.getType() });
      if (moveObjectTo(object, newPoint) == false) 
      {
        delete object;
        return nullptr;
      }
      object->setBody(body);
    }
    break;
  case GameObjectType_Player:
    object = new Player(this, body);
    break;
  case GameObjectType_Enemy:
    object = new Enemy(this, body);
    break;
  case GameObjectType_Bullet:
    object = new Bullet(this, body);
    break;
  case GameObjectType_Bonus:
    object = new Bonus(this, body);
    break;
  case GameObjectType_None:
    break;
  }

  if (object == nullptr)
  {
    return nullptr;
  }

  if (moveObjectTo(object, body.getTopLeft()) == false)
  {
    delete object;
    return nullptr;
  }

  if (m_objects.isFull())
  {
    delete object;
    return nullptr;
  }
  m_objects.pushBack(object);

  return object;
}

bool Game::moveObjectTo(GameObject* object, Point<float> newTopLeft) const
{
  bool canMoveToCell = checkBorder(object, newTopLeft);
  
  if (canMoveToCell == false)
  {
    if (object->getType() == GameObjectType_Bullet) 
    {
      object->setHealth(0);
    }
  }

  Side side = Side_None;
  GameObject* otherObject = checkIntersects(object, newTopLeft, side);
  if (!(otherObject && (object->getType() == GameObjectType_Enemy)))
  {
    object->setPoint(newTopLeft);
  }
  
  if (otherObject) 
  {
    object->intersect(otherObject, side);
    canMoveToCell = false;
  }

  return canMoveToCell;
}

bool Game::checkBorder(const GameObject* object, Point<float>& newTopLeft)
{
  const auto size = object->getBody().getSize();
  const auto lcdMaxX = static_cast<float>(LCD_GetXSize()) - size.width;
  const auto lcdMaxY = static_cast<float>(LCD_GetYSize()) - size.height;

  bool canMoveToCell = true;
  if (newTopLeft.x < 0)
  {
    newTopLeft.x = 0;
    canMoveToCell = false;
  }
  else if (newTopLeft.x > lcdMaxX)
  {
    newTopLeft.x = lcdMaxX;
    canMoveToCell = false;
  }
  if (newTopLeft.y < 0)
  {
    newTopLeft.y = 0;
    canMoveToCell = false;
  }
  else if (newTopLeft.y > lcdMaxY)
  {
    newTopLeft.y = lcdMaxY;
    canMoveToCell = false;
  }

  return canMoveToCell;
}

GameObject* Game::checkIntersects(const GameObject* exceptObject, Point<float>& newTopLeft, Side& side) const
{
  const auto exceptObjectBody = exceptObject->getBody();
  const Size exceptObjectSize = exceptObjectBody.getSize();
  const Point<float> newBottomRight = (newTopLeft + exceptObjectSize - 1);
  const Point<float> prevTopLeft = exceptObjectBody.getTopLeft();
  const Point<float> prevBottomRight = exceptObjectBody.getBottomRight();
  const Point<int> newTopLeftInt = newTopLeft.cast<int>();
  const Point<int> newBottomRightInt = (newTopLeft + exceptObjectSize - 1).cast<int>();

  GameObject* intersectObject = nullptr;
  const bool isTypeBullet = (exceptObject->getType() == GameObjectType_Bullet);

  for (const auto& object : m_objects)
  {
    if (object && (object != exceptObject))
    {
      const auto objectBody = object->getBody();
      const Point<float> objectTopLeft = objectBody.getTopLeft();
      const Point<float> objectBottomRight = objectBody.getBottomRight();
      const Point<int> objectTopLeftInt = objectTopLeft.cast<int>();
      const Point<int> objectBottomRightInt = objectBottomRight.cast<int>();

      // ReSharper disable once CppTooWideScope
      const bool isObjectCollisionCheckCompleted = (objectBody.getType() == GameObjectType_Bullet) && intersectObject;
      if (isObjectCollisionCheckCompleted)
      {
        return intersectObject;
      }
      if (isTypeBullet
            ? ((newTopLeft <= objectBottomRight) && (newBottomRight >= objectTopLeft))
            : ((newTopLeftInt <= objectBottomRightInt) && (newBottomRightInt >= objectTopLeftInt)))
      {
        intersectObject = object;

        if (prevTopLeft.x >= objectBottomRight.x)
        {
          newTopLeft.x = objectBottomRight.x + 0.01f;
          side = Side_Right;
        }
        else if (prevBottomRight.x <= objectTopLeft.x)
        {
          newTopLeft.x = objectTopLeft.x - exceptObjectSize.width;
          side = Side_Left;
        }
        else if (prevTopLeft.y >= objectBottomRight.y)
        {
          newTopLeft.y = objectBottomRight.y + 0.01f;
          side = Side_Bottom;
        }
        else if (prevBottomRight.y <= objectTopLeft.y)
        {
          newTopLeft.y = objectTopLeft.y - exceptObjectSize.height;
          side = Side_Top;
        }
      }
    }
  }
  return intersectObject;
}

void Game::addEnemy(GameObject* enemy)
{
  m_enemies.pushBack(enemy);
}

size_t Game::findIndexOfSprite(const GUI_BITMAP* targetBmp) const
{
  for (int i = 0; i < kGameNumberOfSprites; ++i) 
  {
    if (m_sprites[i].pBitmap == targetBmp) 
    {
      return i;
    }
  }
  return -1;
}

void GameError(const char *s)
{
  GUI_SetBkColor(GUI_RED);
  GUI_Clear();
  GUI_SetColor(GUI_BLACK);
  GUI_SetFont(&GUI_Font8_ASCII);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_DispStringAt(s, 5, 5);
  __disable_irq();
  while (true)
  {
  }
}