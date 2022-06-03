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
    int iH;
    int hist[5];

    cT characterType;

    CCharacter(char _s);

    virtual void decideNextMove(char & _i, int playerAtCol, int playerAtLine) = 0;

    virtual ~CCharacter();
};