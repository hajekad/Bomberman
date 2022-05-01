#include <iostream>
#include <ncurses.h>

using namespace std;



int main()
{
  bool escapeSequence = 1;

  initscr();
  
  while(escapeSequence)
  {
    

    refresh();
  }
  endwin();

  return 0;
}
