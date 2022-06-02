#include "gameLoop.hpp"

char CGameLoop::getInput(WINDOW * _w)
{
    cbreak();
    wtimeout(_w, 0);
    char ret;
    ret = wgetch(_w);
    flushinp();
    if(ret != ERR) return ret;
    return 'H';
}

CGameLoop::CGameLoop()
{
    currMap = nullptr;
}

void CGameLoop::start(WINDOW * _w)
{
    wmove(_w, 1, getmaxx(_w)/2 - 4);
    wprintw(_w, "BOMBERMAN");
    wmove(_w, 2, getmaxx(_w)/2 - 13);
    wprintw(_w, "press any button to start");

    refresh();
    wrefresh(_w);

    running = 1;
    inMenu = 1;
    wgetch(_w);
}

void CGameLoop::mainThread(WINDOW * _w)
{
    std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();

    while(running)
    {
        //cbreak();

        if(inMenu)
        {
            gameMenu.render(_w);
            
            char tmp = 0;

            while(tmp == 0)
            {
                tmp = getInput(_w);
                if(tmp == 'n')
                {
                    inMenu = 0;
                    currMap = new CWorld(_w);
                    if(currMap != nullptr) delete currMap;
                }
                else if(tmp == 'f')
                {
                    inMenu = 0;
                    int map = 1;
                    if(currMap != nullptr) delete currMap;
                    currMap = new CWorld(map, _w);
                }
                else if(tmp == 'e') running = 0;
            }
        }
        else
        {
            char _in = getInput(_w);

            if(_in == 27)
            {
                inMenu = 1; // 27 == ESC
            }
            currMap->update(_in);
            
            render(_w);
        }

        t += std::chrono::milliseconds(50);
        std::this_thread::sleep_until(t);
    }
    if(currMap != nullptr) delete currMap;
}

void CGameLoop::render(WINDOW * _w)
{
    wclear(_w);
    box(_w, 0, 0);

    int foo = 0;

    int x = 1;
    int y = 1;
    
    for(auto i = currMap->worldMap.begin(); i != currMap->worldMap.end(); i++)
    {
        foo++;
        for(auto j = i->begin(); j != i->end(); j++)
        {
            wmove(_w, y, x);
            char _c[1];
            _c[0] = j->texture;
            if(j->currState == OCCUPIED)
            {
                start_color();
                init_pair(2, COLOR_BLACK, COLOR_BLUE);
                wattron(_w,COLOR_PAIR(2));
                waddch(_w, _c[0]);
                wattroff(_w,COLOR_PAIR(2));
            }
            else wprintw(_w, _c);
            x++;
        }
        y++;
        x = 1;
    }
    
    refresh();
    wrefresh(_w);
}