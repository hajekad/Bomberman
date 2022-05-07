#include "gameLoop.hpp"

int main()
{
  CGameLoop session;
  
  initscr();

  session.start();

  session.mainThread();

  endwin();

  return 0;
}
