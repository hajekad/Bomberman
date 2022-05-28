#pragma once

#include <ncurses.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <chrono>
#include <thread>

#include "menu.hpp"
#include "world.hpp"

class CGameLoop
{
    private: 
        bool running;
        bool inMenu;
        CMenu gameMenu;
        CWorld * currMap;

    public:
        CGameLoop();

        char getInput(WINDOW * _w);

        void start(WINDOW * _w);

        void mainThread(WINDOW * _w);

        void render(WINDOW * _w);
};
