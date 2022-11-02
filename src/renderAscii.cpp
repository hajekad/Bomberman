#include "renderAscii.hpp"

CAscii::CAscii(WINDOW * _w) : CRender(_w)
{
    
}

void CAscii::render(std::vector<std::vector<CCell>> & _m)
{
    wclear(window);
    box(window, 0, 0);

    int foo = 0;

    int x = 1;
    int y = 1;

    //bool hasplayer = 0;
    
    for(auto i = _m.begin(); i != _m.end(); i++)
    {
        foo++;
        for(auto j = i->begin(); j != i->end(); j++)
        {
            wmove(window, y, x);
            char _c[1];
            _c[0] = j->texture;

            //if(_c[0] == 'P') hasplayer = 1;

            if(j->currState == OCCUPIED)
            {
                start_color();
                init_pair(2, COLOR_BLACK, COLOR_BLUE);
                wattron(window,COLOR_PAIR(2));
                waddch(window, _c[0]);
                wattroff(window,COLOR_PAIR(2));
            }
            else if(j->bomb != nullptr)
            {
                start_color();
                init_pair(2, COLOR_BLACK, COLOR_RED);
                wattron(window,COLOR_PAIR(2));
                _c[0] = 'o';
                waddch(window, _c[0]);
                wattroff(window,COLOR_PAIR(2));
            }
            else wprintw(window, _c);
            x++;
        }
        y++;
        x = 1;
    }
    
    refresh();
    wrefresh(window);
}