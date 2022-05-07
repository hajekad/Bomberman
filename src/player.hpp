#pragma once

#include "character.hpp"
#include "weapon.hpp"

class CPlayer : public CCharacter
{
private:
    int damage;
    int speed;

public:
    void placeBomb();
    void useSecond();
    void move()override;
    void perish()override;
};