#pragma once

#include <string>
#include <vector>
#include <ncurses.h>
#include <sstream>
#include <cstring>

class CMenu
{  
public:
    void render(WINDOW * _w);

    void endGame(WINDOW * _w, int _t);

    std::string pickLevel(WINDOW * _w);
private:
    bool isnum(char _a);
};
