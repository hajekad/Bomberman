#include "menu.hpp"

void CMenu::render(WINDOW * _w)
{
    wclear(_w);
    
    box(_w, 0, 0);
    
    wmove(_w, 1, getmaxx(_w)/2 - 4);
    wprintw
    (
        _w,
        "BOMBERMAN"
    );
    wmove(_w, 2, getmaxx(_w)/2 - 5);
    wprintw
    (
        _w,
        "New game[N]"
    );
    wmove(_w, 3, getmaxx(_w)/2 - 6);
    wprintw
    (
        _w,
        "Load file[F]"
    );
    wmove(_w, 4, getmaxx(_w)/2 - 4);
    wprintw
    (
        _w,
        "EXIT[e]"
    );

    refresh();
    wrefresh(_w);
}