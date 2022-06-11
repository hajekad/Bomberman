#pragma once

#include <ncurses.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <chrono>
#include <thread>

#include "menu.hpp"
#include "world.hpp"
#include "renderAscii.hpp"
#include "renderPixel.hpp"

#define _NEW_GAME 'n'
#define _LOAD_FILE 'f'
#define _CHANGE_GRAPHICS 'g'
#define _EXIT 'e'
#define _ESC 27

#define _MAP_COUNT 10

class CGameLoop
{
    private: 
        bool running; /** *@brief true if game should still run, false otherwise */
        
        bool inMenu; /** *@brief true if game should enter menu */
        
        CMenu gameMenu; /** *@brief CMenu to be used in this game */
        
        CWorld * currMap; /** *@brief current selected map to be played on */

        std::string fileName;

        std::unique_ptr<CRender> renderer;

        bool lowGraphics;

    public:
        CGameLoop(WINDOW * _w);

        /**
         * @brief get input from player 
         * 
         * @param _w window that is used for the current game session
         * @return char 
         */
        char getInput(WINDOW * _w);

        /**
         * @brief starts the main game loop and displays initial screen
         * 
         * @param _w window that is used for the current game session
         */
        void start(WINDOW * _w);

        /**
         * @brief runs as long as running bool is true, calls menu methods, render and map update
         * 
         * @param _w window that is used for the current game session
         */
        void mainThread(WINDOW * _w);

        /**
         * @brief draws the current state of game into the konsole
         * 
         * @param _w window that is used for the current game session 
         */
        void render(WINDOW * _w);

        void writeToFile(int _t);
};
