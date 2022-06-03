#pragma once

#include <random>
#include <time.h>
#include <iostream>
#include <stdlib.h>

#include "character.hpp"

class CEnemy : public CCharacter
{
private:
    char skin;
    int hp;
    int panicCnt;

public:
    CEnemy(char _s);

    void attack(CCharacter & toAttack);

    bool onePlace();

    void decideNextMove(char & _i, int playerAtCol, int playerAtLine);
    
    void receiveDmg(int _d);
};