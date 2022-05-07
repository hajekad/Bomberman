#pragma once

#include <ncurses.h>
#include <unistd.h>

#include "menu.hpp"
//#include "world.hpp"

class CGameLoop
{
    private: 
        bool running;
        bool inMenu;
        CMenu gameMenu;
        //CWorld * currMap;

    public:
        void start();

        void mainThread();

        void render();
};
