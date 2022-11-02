#include "gameLoop.hpp"

int main()
{
  initscr();

  int y, x;
  getmaxyx(stdscr, y, x);

  WINDOW * win = newwin(y, x, 0, 0);
  box(win, 0, 0);
  refresh();
  wrefresh(win);
  cbreak();

  CGameLoop session(win);
  session.start(win);

  session.mainThread(win);

  endwin();

  return 0;
}
