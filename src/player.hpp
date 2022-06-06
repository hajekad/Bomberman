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
    int score;

private:
    int damage;
    int speed;
    int tTE;
    int range;

public:
    CPlayer(char _s);

    void placeBomb(CCell & _c);

    void changeRange(int _r);

    void changeTTE();
        
    void decideNextMove(char & _i, int playerAtCol, int playerAtLine);
};