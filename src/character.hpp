#pragma once

#include <ctype.h>
#include <stdlib.h>
#include <random>

#include "weapon.hpp"

enum cT
{
    PLAYER,
    NPC,
    ENEMY
};

class CCharacter
{
public:
    char skin; /** *@brief skin of the character to be displayed to the occupied cell */

    int line, column; /** *@brief current coordinates of the character */

    int speed; /** *@brief legacy variable that could be specific only to CEnemy but is already worked with from here, used for the moduling of random in decide move */

    bool stayed; /** *@brief true if character stayed in one place from the last round */

    int hist[5];    /** *@brief history of moves from the last 5 move tryes */

    int iH; /** *@brief history array iterrator */

    bool second;

    cT characterType;

    int score;

    /**
     * @param _s stands for skin
     * @return void return value;
     */
    CCharacter(char _s);

    virtual ~CCharacter();
    
    /** 
     * @param is virtual, can't be called from here(works from CPlayer(idle) and CEnemy(essential))
     * @return void return value
     */ 
    virtual std::shared_ptr<CWeapon> decideNextMove(char & _i, int playerAtCol, int playerAtLine,  std::vector<std::pair<int, int>> & _tA) = 0;

    virtual void change() = 0;
};