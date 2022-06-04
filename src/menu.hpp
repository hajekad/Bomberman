#pragma once

#include <string>
#include <vector>
#include <ncurses.h>

class CMenu
{  
public:
    void render(WINDOW * _w);

    std::string pickLevel(WINDOW * _w);
private:
    bool isnum(char _a);
};
