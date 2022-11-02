#pragma once

#include <ncurses.h>

#include "renderer.hpp"

#define _POSITION_HEIGHT 5
#define _POSITION_WIDTH 3

class CPixel : public CRender
{
private:    
    void bomb(int _l, int _c);
    
    void free(int _l, int _c);
    
    void destroyable(int _l, int _c);
    
    void unbreakable(int _l, int _c);

    void bonus(int _l, int _c);

    void draw();

    std::vector<std::vector<int>> toBeDisplayed;

public:
        CPixel(WINDOW * _w);

        void render(std::vector<std::vector<CCell>> & _m);
};