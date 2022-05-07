#include "menu.hpp"

void CMenu::render(bool & running, bool & inMenu)
{
    clear();
    
    move(10,20);
    printw
    (
        "BOMBERMAN\n\tNew game[N]\tLoad file[F]\n\t\t EXIT[e]"
    );
    
    char ret = getch();
    
    if(ret == 'e') running = 0;
    else if(ret == 'n' || ret == 'f') inMenu = 0;
}