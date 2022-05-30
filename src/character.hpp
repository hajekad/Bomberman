#pragma once

#include <ctype.h>

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
    cT characterType;

    virtual void decideNextMove(char & _i) = 0;

    CCharacter(char _s);
    ~CCharacter();
};