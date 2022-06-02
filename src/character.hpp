#pragma once

#include <ctype.h>
#include <stdlib.h>
#include <random>

enum cT
{
    PLAYER,
    NPC,
    ENEMY
};

class CCharacter
{
public:
    char skin;
    int line, column;
    int speed;
    bool stayed;

    cT characterType;

    virtual void decideNextMove(char & _i, int playerAtCol, int playerAtLine) = 0;

    CCharacter(char _s);
    virtual ~CCharacter();
};