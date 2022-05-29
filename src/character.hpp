#pragma once

#include <ctype.h>

class CCharacter
{
public:
    char skin;
    int line, column;
private:
    enum cT
    {
        PLAYER,
        NPC,
        ENEMY
    };

public:
    cT characterType; 
    CCharacter(char _s);
    ~CCharacter();
};