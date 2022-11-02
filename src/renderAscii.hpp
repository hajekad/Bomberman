#pragma once

#include <ncurses.h>

#include "renderer.hpp"

class CAscii : public CRender
{
public:
        CAscii(WINDOW * _w);

        void render(std::vector<std::vector<CCell>> & _m);
};