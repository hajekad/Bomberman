#pragma once

#include <string>
#include <vector>
#include <ncurses.h>
#include <sstream>
#include <cstring>

class CMenu
{  
public:
    /**
     * @brief draws out the current menu page
     * 
     * @param _w window that is used for the current game session 
     */
    void render(WINDOW * _w);

    /**
     * @brief displays the end game screen with score
     * 
     * @param _w window that is used for the current game session
     * @param _t highest score achieved in this game by any player
     */
    void endGame(WINDOW * _w, int _t);

    /**
     * @brief lets the user pick the desired map
     * 
     * @param _w window that is used for the current game session
     * @return std::string name of the picked map
     */
    std::string pickLevel(WINDOW * _w);

    /**
     * @brief decides if _a is a digit
     * 
     * @param _a 
     * @return true if _a is a digit
     * @return false if _a is not a digit
     */
    bool isnum(char _a);
};
