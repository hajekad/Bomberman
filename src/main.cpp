#include "gameLoop.hpp"

using namespace std;

int main()
{
  CGameLoop session;
  
  initscr();

  session.start();

  endwin();

  return 0;
}
