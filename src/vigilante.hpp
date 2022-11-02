#pragma once

#include <random>
#include <time.h>
#include <iostream>
#include <stdlib.h>

#include "character.hpp"
#include "weapon.hpp"

#define _START_HP 15
#define _PANIC_ARRAY_SIZE 5
#define _INIT_DIR 5
#define _PANIC_BOOST 7
#define _START_RANGE 2
#define _START_TIME_TO_EXPLODE 4
#define _POSSIBLE_OUTCOMES 3
#define _LONGER_TIME 2

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class CVigilante : public CCharacter
{
private:    
    int tTE; /** *@brief time to explode, used for bomb */
    
    int range; /** *@brief range of players bombs */

    /**
     * @brief places a bomb to CCell _c
     * 
     * @param _c Cell to place a bomb to
     */
    std::shared_ptr<CWeapon> placeBomb();    

    char skin; /** *@brief skin of the character to be displayed to the occupied cell */

    int hp; /** *@brief legacy variable that is not to be touched and also does nothing special */

    int panicCnt; /** *@brief can enter panic mode that only lasts so many moves */

public:
    std::shared_ptr<CWeapon> currBomb; /** *@brief pointer to a currently placed bomb */
    
    bool placedBomb; /** *@brief true if player can place a bomb */

    CVigilante(char _s);

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
