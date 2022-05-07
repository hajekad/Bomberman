#pragma once

#include "character.hpp"

class CEnemy : public CCharacter
{
private:
    int damage;
    int hp;
    int speed;
    
public:
    void attack(CCharacter & toAttack);
    
    void move()override;
    void perish()override;
};