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
                    std::string tmp = "examples/map";
                    tmp +=  ((std::rand() % 10) + '0');
                    tmp += ".txt";
                    if(currMap != nullptr) delete currMap;
                    currMap = new CWorld(tmp, _w);
                }
                else if(tmp == 'f')
                {
                    inMenu = 0;
                    std::string map = gameMenu.pickLevel(_w);
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

            int _t = currMap->update(_in);

            if(_t == 1) inMenu = 1;
            else if(_t > 1)
            {
                gameMenu.endGame(_w, _t);
                inMenu = 1;
            }
            
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

    //bool hasplayer = 0;
    
    for(auto i = currMap->worldMap.begin(); i != currMap->worldMap.end(); i++)
    {
        foo++;
        for(auto j = i->begin(); j != i->end(); j++)
        {
            wmove(_w, y, x);
            char _c[1];
            _c[0] = j->texture;

            //if(_c[0] == 'P') hasplayer = 1;

            if(j->currState == OCCUPIED)
            {
                start_color();
                init_pair(2, COLOR_BLACK, COLOR_BLUE);
                wattron(_w,COLOR_PAIR(2));
                waddch(_w, _c[0]);
                wattroff(_w,COLOR_PAIR(2));
            }
            else if(j->bomb != nullptr)
            {
                start_color();
                init_pair(2, COLOR_BLACK, COLOR_RED);
                wattron(_w,COLOR_PAIR(2));
                _c[0] = 'o';
                waddch(_w, _c[0]);
                wattroff(_w,COLOR_PAIR(2));
            }
            else wprintw(_w, _c);
            x++;
        }
        y++;
        x = 1;
    }

    //if(!hasplayer) inMenu = 1;
    
    refresh();
    wrefresh(_w);
}