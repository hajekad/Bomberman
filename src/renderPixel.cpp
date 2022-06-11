#include "renderPixel.hpp"

CPixel::CPixel(WINDOW * _w) : CRender(_w)
{
    
}

void CPixel::render(std::vector<std::vector<CCell>> & _m)
{
    wclear(window);
    box(window, 0, 0);
    start_color();
    int foo = 0;

    int x = 0;
    int y = 0;

    //bool hasplayer = 0;
    
    for(auto i = _m.begin(); i != _m.end(); i++)
    {
        foo++;
        for(auto j = i->begin(); j != i->end(); j++)
        {
            if(j->currState == OCCUPIED)
            {
                if(j->occupiedBy.get()->characterType == PLAYER)
                    player(3 * y, 3 * x);
                else
                    badGuy(3 * y, 3 * x);
            }
            else if(j->bomb != nullptr)
            {
                bomb(3 * y, 3 * x);
            }
            else 
            {
                switch(j->currState)
                {
                    case FREE:
                        free(3 * y, 3 * x);
                        break;
                    case DESTROYABLE:
                        destroyable(3 * y, 3 * x);
                        break;
                    case UNBREAKABLE:
                        unbreakable(3 * y, 3 * x);
                        break;

                    default: break;
                }
            }
            x++;
        }
        y++;
        x = 1;
    }
    
    refresh();
    wrefresh(window);
}

void CPixel::player(int _l, int _c)
{
    int _ib = 0;
    int blocks[]
    {
        COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA,
        COLOR_CYAN,    COLOR_CYAN,    COLOR_MAGENTA,
        COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA,
        COLOR_MAGENTA, COLOR_BLUE, COLOR_MAGENTA,
        COLOR_MAGENTA, COLOR_BLUE, COLOR_MAGENTA
    };

    for(int renderLine = 1; renderLine < 6; renderLine++)
    {
        for(int renderColumn = 1; renderColumn < 4; renderColumn++)
        {
            start_color();
            move(_l + renderLine, _c + renderColumn);
            init_pair(2, blocks[_ib], blocks[_ib]);
            wattron(window,COLOR_PAIR(2));
            waddch(window, '_');
            wattroff(window,COLOR_PAIR(2));
            _ib++;
        }
    }

}

void CPixel::badGuy(int _l, int _c)
{
    int _ib = 0;
    int blocks[]
    {
        COLOR_RED, COLOR_RED,  COLOR_RED,
        COLOR_RED, COLOR_CYAN, COLOR_CYAN,
        COLOR_RED, COLOR_RED,  COLOR_RED,
        COLOR_RED, COLOR_BLUE, COLOR_RED,
        COLOR_RED, COLOR_BLUE, COLOR_RED
    };

    for(int renderLine = 1; renderLine < 6; renderLine++)
    {
        for(int renderColumn = 1; renderColumn < 4; renderColumn++)
        {
            start_color();
            move(_l + renderLine, _c + renderColumn);
            init_pair(2, blocks[_ib], blocks[_ib]);
            wattron(window,COLOR_PAIR(2));
            waddch(window, '_');
            wattroff(window,COLOR_PAIR(2));
            _ib++;
        }
    }
}

void CPixel::bomb(int _l, int _c)
{
    int _ib = 0;
    int blocks[]
    {
        COLOR_BLUE, COLOR_BLUE,  COLOR_YELLOW,
        COLOR_BLUE, COLOR_WHITE, COLOR_CYAN,
        COLOR_BLACK, COLOR_BLACK,  COLOR_RED,
        COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
        COLOR_BLACK, COLOR_BLACK, COLOR_BLACK
    };

    for(int renderLine = 1; renderLine < 6; renderLine++)
    {
        for(int renderColumn = 1; renderColumn < 4; renderColumn++)
        {
            start_color();
            move(_l + renderLine, _c + renderColumn);
            init_pair(2, blocks[_ib], blocks[_ib]);
            wattron(window,COLOR_PAIR(2));
            waddch(window, '.');
            wattroff(window,COLOR_PAIR(2));
            _ib++;
        }
    }
}

void CPixel::free(int _l, int _c)
{
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    for(int renderLine = 1; renderLine < 6; renderLine++)
    {
        for(int renderColumn = 1; renderColumn < 4; renderColumn++)
        {
            start_color();
            move(_l + renderLine, _c + renderColumn);
            wattron(window,COLOR_PAIR(2));
            waddch(window, '_');
            wattroff(window,COLOR_PAIR(2));
        }
    }
}

void CPixel::destroyable(int _l, int _c)
{
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    int cnt = 0;
    for(int renderLine = 1; renderLine < 6; renderLine++)
    {
        for(int renderColumn = 1; renderColumn < 4; renderColumn++)
        {
            start_color();
            if(cnt % 2) init_pair(2, COLOR_BLUE, COLOR_BLUE);
            else init_pair(2, COLOR_BLACK, COLOR_BLACK);

            move(_l + renderLine, _c + renderColumn);
            wattron(window,COLOR_PAIR(2));
            waddch(window, '_');
            wattroff(window,COLOR_PAIR(2));

            cnt++;
        }
    }
}

void CPixel::unbreakable(int _l, int _c)
{
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    for(int renderLine = 1; renderLine < 6; renderLine++)
    {
        for(int renderColumn = 1; renderColumn < 4; renderColumn++)
        {
            start_color();
            move(_l + renderLine, _c + renderColumn);
            wattron(window,COLOR_PAIR(2));
            waddch(window, '_');
            wattroff(window,COLOR_PAIR(2));
        }
    }
}
