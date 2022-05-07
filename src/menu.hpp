#pragma once

#include <string>
#include <vector>
#include <ncurses.h>

//#include "world.hpp"

class CMenu
{  
public:
    CMenu();
    ~CMenu();

    //CWorld * loadLevel();
    int pickLevel();
    void render(bool & running, bool & inMenu);
    void newGame();
};

