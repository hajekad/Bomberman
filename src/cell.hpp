#pragma once

#include <memory>
#include "player.hpp"
#include "enemy.hpp"
//#include "npc.hpp"

class CPlayer;

enum state
{
    FREE,
    OCCUPIED,
    UNBREAKABLE,
    DESTROYABLE,
    BOMB
};

class CCell
{
public:
    char texture;
    state currState;
    std::shared_ptr<CCharacter> occupiedBy;
    std::shared_ptr<CWeapon> bomb;
    
    CCell(char _c);
    ~CCell();
};
