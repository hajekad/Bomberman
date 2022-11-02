#pragma once

#include <ctype.h>
#include <stdlib.h>
#include <random>
#include <ncurses.h>
#include <memory>

#include "weapon.hpp"

#define _PLAYER 'P'
#define _ENEMY 'E'
#define _MAX_SPEED_DIFF 5
#define _MAX_SPEED 4

#define _POSITION_HEIGHT 5
#define _POSITION_WIDTH 3

#define _UP 'w'
#define _RIGHT 'd'
#define _DOWN 's'
#define _LEFT 'a'
#define _STAY 'H'

enum cT
{
    PLAYER,
    VIGILANTE,
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

    bool alive;
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

    virtual const void draw(std::vector<std::vector<int>> & toBeDisplayed) = 0;
};
