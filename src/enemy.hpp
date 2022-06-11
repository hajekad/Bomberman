#pragma once

#include <random>
#include <time.h>
#include <iostream>
#include <stdlib.h>

#include "character.hpp"

#define _START_HP 15
#define _PANIC_ARRAY_SIZE 5
#define _INIT_DIR 5
#define _PANIC_BOOST 7

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class CEnemy : public CCharacter
{
private:
    char skin; /** *@brief skin of the character to be displayed to the occupied cell */
    int hp; /** *@brief legacy variable that is not to be touched and also does nothing special */ 
    int panicCnt; /** *@brief can enter panic mode that only lasts so many moves */

public:
    CEnemy(char _s);

    /**
     *@brief if all the coordinates in history are the same then true
     *
     *@return true if hist has 5 same numbers, false otherwise
     */
    bool onePlace();

    /**
     * @brief decides the next move of this, goes either full panic mode or the shortest naive way to the player 
     * 
     * @param _i stores the decided direction here
     * @param playerAtCol desired column of an enemy
     * @param playerAtLine desired line of an enemy
     */
    std::shared_ptr<CWeapon> decideNextMove(char & _i, int playerAtCol, int playerAtLine,  std::vector<std::pair<int, int>> & _tA);

    void change();

    const void draw(std::vector<std::vector<int>> & toBeDisplayed);
};