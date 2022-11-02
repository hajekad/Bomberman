#pragma once

#include <ncurses.h>
#include <vector>

#include "cell.hpp"

class CRender
{
    protected:
        WINDOW * window;
    public:
        CRender(WINDOW * _w);

        virtual void render(std::vector<std::vector<CCell>> & _m) = 0;
};