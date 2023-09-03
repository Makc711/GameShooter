// Include
#include "CtoCppBridge.hpp"
#include "Game.hpp"

void EventLoopCpp()
{
  while (true)
  {
    const auto game = new Game();
    game->setupSystem();
    while (game->loop()){}
    delete game;
  }
}

extern "C"
{
  void EventLoopC()
  {
    EventLoopCpp();
  }
}