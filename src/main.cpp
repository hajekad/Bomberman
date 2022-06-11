#include "gameLoop.hpp"

int main()
{
  initscr();

  int y, x;
  getmaxyx(stdscr, y, x);

  WINDOW * win = newwin(y, 70, 0, x/4);
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
