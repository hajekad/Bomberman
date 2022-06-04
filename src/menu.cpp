#include "menu.hpp"

void CMenu::render(WINDOW * _w)
{
    wclear(_w);
    
    box(_w, 0, 0);
    
    wmove(_w, 1, getmaxx(_w)/2 - 4);
    wprintw(_w, "BOMBERMAN");

    wmove(_w, 2, getmaxx(_w)/2 - 5);
    wprintw(_w, "New game[N]");

    wmove(_w, 3, getmaxx(_w)/2 - 6);
    wprintw(_w, "Load file[F]");

    wmove(_w, 4, getmaxx(_w)/2 - 4);
    wprintw(_w, "EXIT[e]");

    refresh();
    wrefresh(_w);
}

std::string CMenu::pickLevel(WINDOW * _w)
{
    std::string ret = "examples/map";
    wclear(_w);
    
    box(_w, 0, 0);
    
    wmove(_w, 5, getmaxx(_w)/2 - 22);
    wprintw(_w, "Enter the number of desired level. (0 - 9)");

    wmove(_w, 7, getmaxx(_w)/2 - 4);
    nocbreak();
    wtimeout(_w, INT32_MAX);

    char tmp = wgetch(_w);
    while(!isnum(tmp))
    {
        wmove(_w, 7, getmaxx(_w)/2 - 4);
        flushinp();
        tmp = wgetch(_w);
    }
    ret += tmp;
    ret += ".txt";
    
    cbreak();
    wtimeout(_w, 0);

    return ret;
}

bool CMenu::isnum(char _a)
{
    switch(_a)
    {
        case '0': break;
        case '1': break;
        case '2': break;
        case '3': break;
        case '4': break;
        case '5': break;
        case '6': break;
        case '7': break;
        case '8': break;
        case '9': break;

        default: return false;
    }

    return true;
}
