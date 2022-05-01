#include "gameLoop.hpp"

void CGameLoop::start()
{
    move(20, 20);
    printw("BOMBERMAN\n\tpress any button to start\n");
    running = 1;
    inMenu = 1;
    getch();
 
}

void CGameLoop::mainThread()
{
    while(running)
    {
        if(inMenu)
        {
            
        }
    }
}