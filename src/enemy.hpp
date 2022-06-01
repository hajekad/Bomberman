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
    int speed;
    
public:
    CEnemy(char _s);

    void attack(CCharacter & toAttack);

    void decideNextMove(char & _i);
    
    void receiveDmg(int _d);
};