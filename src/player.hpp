#pragma once

#include "character.hpp"
//#include "weapon.hpp"

class CPlayer : public CCharacter
{
private:
    int damage;
    int speed;

public:
    CPlayer(char _s);

    void placeBomb();
    void useSecond();
    
    void decideNextMove(char & _i, int playerAtCol, int playerAtLine);
};