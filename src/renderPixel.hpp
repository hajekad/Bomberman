#pragma once

#include <ncurses.h>

#include "renderer.hpp"

class CPixel : public CRender
{
private:
    void player(int _l, int _c);
    
    void badGuy(int _l, int _c);
    
    void bomb(int _l, int _c);
    
    void free(int _l, int _c);
    
    void destroyable(int _l, int _c);
    
    void unbreakable(int _l, int _c);

public:
        CPixel(WINDOW * _w);

        void render(std::vector<std::vector<CCell>> & _m);
};