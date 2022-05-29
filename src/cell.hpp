#pragma once

#include <memory>
#include "character.hpp"
#include "player.hpp"
//#include "enemy.hpp"
//#include "npc.hpp"

enum state
{
    FREE,
    OCCUPIED,
    UNBREAKABLE,
    DESTROYABLE
};

class CCell
{
public:
    char texture;
    state currState;
    std::shared_ptr<CCharacter> occupiedBy;
private:
public:
    CCell(char _c);
    ~CCell();
};
