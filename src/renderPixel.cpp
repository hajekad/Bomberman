#include "renderPixel.hpp"

CPixel::CPixel(WINDOW * _w) : CRender(_w)
{
    
}

void CPixel::draw()
{
    wclear(window);
    init_pair(0, COLOR_GREEN, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_GREEN, COLOR_YELLOW);
    init_pair(4, COLOR_GREEN, COLOR_BLUE);
    init_pair(5, COLOR_GREEN, COLOR_MAGENTA);
    init_pair(6, COLOR_GREEN, COLOR_CYAN);
    init_pair(7, COLOR_GREEN, COLOR_WHITE);
    int _l, _c;
    _l = _c = 1;

    auto i = toBeDisplayed.begin();
    i++;
    auto ib = toBeDisplayed.end();
    ib--;

    for(; i != ib; i++)
    {
        auto j = i->begin();
        j++;
        auto jb = i->end();
        jb--;
        for(;j != jb; j++)
        {
            wmove(window, _l, _c);

            start_color();

            wattron(window,COLOR_PAIR(*j));

            waddch(window, ' ');

            wattroff(window,COLOR_PAIR(*j));

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
    box(window, 0, 0);
    start_color();
    int foo = 0;

    int x = 0;
    int y = 0;

    //bool hasplayer = 0;
    
    for(auto i = _m.begin(); i != _m.end(); i++)
    {
        for(int j = 0; j < _POSITION_HEIGHT; j++)
        {
            std::vector<int> tmp;
            toBeDisplayed.push_back(tmp);
        }
        foo++;
        for(auto j = i->begin(); j != i->end(); j++)
        {
            if(j->currState == OCCUPIED)
                j->occupiedBy.get()->draw(toBeDisplayed);
            else if(j->bomb != nullptr)
                bomb(_POSITION_HEIGHT * y, _POSITION_WIDTH * x);
            else if(j->hasBonus)
                bonus(_POSITION_HEIGHT * y, _POSITION_WIDTH * x);
            else 
                switch(j->currState)
                {
                    case FREE:
                        free(_POSITION_HEIGHT * y, _POSITION_WIDTH * x);
                        break;
                    case DESTROYABLE:
                        destroyable(_POSITION_HEIGHT * y, _POSITION_WIDTH * x);
                        break;
                    case UNBREAKABLE:
                        unbreakable(_POSITION_HEIGHT * y, _POSITION_WIDTH * x);
                        break;

                    default: break;
                }
                
            x++;
        }
        y++;
        x = 0;
    }
    
    draw();
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

    for(int renderLine = 0; renderLine < _POSITION_HEIGHT; renderLine++)
    {
        for(int renderColumn = 0; renderColumn < _POSITION_WIDTH; renderColumn++)
        {
            toBeDisplayed.at(_l + renderLine).push_back(blocks[_ib]);
            _ib++;
        }
    }
}

void CPixel::bonus(int _l, int _c)
{
    int _ib = 0;
    int blocks[]
    {
        COLOR_BLUE, COLOR_RED,  COLOR_BLUE,
        COLOR_RED, COLOR_YELLOW, COLOR_RED,
        COLOR_BLUE, COLOR_RED,  COLOR_BLUE,
        COLOR_BLUE, COLOR_GREEN, COLOR_GREEN,
        COLOR_BLUE, COLOR_GREEN, COLOR_BLUE
    };

    for(int renderLine = 0; renderLine < _POSITION_HEIGHT; renderLine++)
    {
        for(int renderColumn = 0; renderColumn < _POSITION_WIDTH; renderColumn++)
        {
            toBeDisplayed.at(_l + renderLine).push_back(blocks[_ib]);
            _ib++;
        }
    }
}

void CPixel::free(int _l, int _c)
{
    for(int renderLine = 0; renderLine < _POSITION_HEIGHT; renderLine++)
        for(int renderColumn = 0; renderColumn < _POSITION_WIDTH; renderColumn++)
            toBeDisplayed.at(_l + renderLine).push_back(COLOR_BLUE);
}

void CPixel::destroyable(int _l, int _c)
{
    int cnt = 0;
    for(int renderLine = 0; renderLine < _POSITION_HEIGHT; renderLine++)
    {
        for(int renderColumn = 0; renderColumn < _POSITION_WIDTH; renderColumn++)
        {
            if(cnt % 2) toBeDisplayed.at(_l + renderLine).push_back(COLOR_BLUE);
            else toBeDisplayed.at(_l + renderLine).push_back(COLOR_BLACK);

            cnt++;
        }
    }
}

void CPixel::unbreakable(int _l, int _c)
{
    for(int renderLine = 0; renderLine < _POSITION_HEIGHT; renderLine++)
        for(int renderColumn = 0; renderColumn < _POSITION_WIDTH; renderColumn++)
            toBeDisplayed.at(_l + renderLine).push_back(COLOR_BLACK);
}
