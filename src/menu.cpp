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

    wmove(_w, 4, getmaxx(_w)/2 - 10);
    wprintw(_w, "Change graphics[G]");

    wmove(_w, 5, getmaxx(_w)/2 - 4);
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
    if(_a >= '0' && _a <= '9') return true;
    return false;
}

void CMenu::endGame(WINDOW * _w, int _t)
{
    int mod = _t % 100;

    wclear(_w);
    
    box(_w, 0, 0);
    
    wmove(_w, 2, getmaxx(_w)/2 - 22);

    if(mod)
    {
        wprintw(_w, "Player");
        waddch(_w, mod + '0');
        wprintw(_w, " won!");
    }
    else wprintw(_w, "Epic tie!");

    wmove(_w, 3, getmaxx(_w)/2 - 22);
    wprintw(_w, "with score: ");

    std::stringstream ss;
    ss << (_t - (_t % 100));
    std::string tmp = ss.str();
    
    for(auto _it = tmp.begin(); _it != tmp.end(); _it++)
    {
        char _c = *_it;
        waddch(_w, _c);
    }

    wmove(_w, 7, getmaxx(_w)/2 - 4);
    wtimeout(_w, INT32_MAX);
    wgetch(_w);
}
