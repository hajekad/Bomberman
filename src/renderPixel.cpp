#include "renderPixel.hpp"

CPixel::CPixel(WINDOW * _w) : CRender(_w)
{
    
}

void CPixel::draw()
{
    init_pair(0, COLOR_GREEN, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_RED);
    init_pair(3, COLOR_GREEN, COLOR_YELLOW);
    init_pair(4, COLOR_GREEN, COLOR_BLUE);
    init_pair(5, COLOR_GREEN, COLOR_MAGENTA);
    init_pair(6, COLOR_GREEN, COLOR_CYAN);
    init_pair(7, COLOR_GREEN, COLOR_WHITE);
    int _l, _c;
    _l = _c = 1;

    for(auto i = toBeDisplayed.begin(); i != toBeDisplayed.end(); i++)
    {
        for(auto j: *i)
        {
            wmove(window, _l, _c);

            start_color();

            wattron(window,COLOR_PAIR(j));

            waddch(window, ' ');

            wattroff(window,COLOR_PAIR(j));

            _c++;
        }
        _c = 1;
        _l++;
    }
    refresh();
    wrefresh(window);
}

void CPixel::render(std::vector<std::vector<CCell>> & _m)
{
    toBeDisplayed.clear();
    wclear(window);
    box(window, 0, 0);
    start_color();
    int foo = 0;

    int x = 0;
    int y = 0;

    //bool hasplayer = 0;
    
    for(auto i = _m.begin(); i != _m.end(); i++)
    {
        for(int j = 0; j < 5; j++)
        {
            std::vector<int> tmp;
            toBeDisplayed.push_back(tmp);
        }
        foo++;
        for(auto j = i->begin(); j != i->end(); j++)
        {
            if(j->currState == OCCUPIED)
            {
                if(j->occupiedBy.get()->characterType == PLAYER)
                    player(5 * y, 3 * x);
                else
                    badGuy(5 * y, 3 * x);
            }
            else if(j->bomb != nullptr)
            {
                bomb(5 * y, 3 * x);
            }
            else 
            {
                switch(j->currState)
                {
                    case FREE:
                        free(5 * y, 3 * x);
                        break;
                    case DESTROYABLE:
                        destroyable(5 * y, 3 * x);
                        break;
                    case UNBREAKABLE:
                        unbreakable(5 * y, 3 * x);
                        break;

                    default: break;
                }
            }
            x++;
        }
        y++;
        x = 0;
    }
    
    draw();
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

    for(int renderLine = 0; renderLine < 5; renderLine++)
    {
        for(int renderColumn = 0; renderColumn < 3; renderColumn++)
        {
            toBeDisplayed.at(_l + renderLine).push_back(blocks[_ib]);
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

    for(int renderLine = 0; renderLine < 5; renderLine++)
    {
        for(int renderColumn = 0; renderColumn < 3; renderColumn++)
        {
            toBeDisplayed.at(_l + renderLine).push_back(blocks[_ib]);
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
        COLOR_BLUE, COLOR_WHITE, COLOR_BLUE,
        COLOR_BLACK, COLOR_BLACK,  COLOR_BLACK,
        COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
        COLOR_BLACK, COLOR_BLACK, COLOR_BLACK
    };

    for(int renderLine = 0; renderLine < 5; renderLine++)
    {
        for(int renderColumn = 0; renderColumn < 3; renderColumn++)
        {
            toBeDisplayed.at(_l + renderLine).push_back(blocks[_ib]);
            _ib++;
        }
    }
}

void CPixel::free(int _l, int _c)
{
    for(int renderLine = 0; renderLine < 5; renderLine++)
        for(int renderColumn = 0; renderColumn < 3; renderColumn++)
            toBeDisplayed.at(_l + renderLine).push_back(COLOR_BLUE);
}

void CPixel::destroyable(int _l, int _c)
{
    int cnt = 0;
    for(int renderLine = 0; renderLine < 5; renderLine++)
    {
        for(int renderColumn = 0; renderColumn < 3; renderColumn++)
        {
            if(cnt % 2) toBeDisplayed.at(_l + renderLine).push_back(COLOR_BLUE);
            else toBeDisplayed.at(_l + renderLine).push_back(COLOR_BLACK);

            cnt++;
        }
    }
}

void CPixel::unbreakable(int _l, int _c)
{
    for(int renderLine = 0; renderLine < 5; renderLine++)
        for(int renderColumn = 0; renderColumn < 3; renderColumn++)
            toBeDisplayed.at(_l + renderLine).push_back(COLOR_BLACK);
}
