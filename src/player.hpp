#pragma once

#include <memory>
#include "character.hpp"
#include "weapon.hpp"
#include "cell.hpp"

class CCell;

class CPlayer : public CCharacter
{
public:
    std::shared_ptr<CWeapon> currBomb;
    bool placedBomb;
private:
    int damage;
    int speed;

public:
    CPlayer(char _s);

    void placeBomb(CCell & _c);
    void useSecond();
    
    void decideNextMove(char & _i, int playerAtCol, int playerAtLine);
};