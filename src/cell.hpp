#pragma once

#include <memory>
#include "character.hpp"
#include "player.hpp"
//#include "enemy.hpp"
//#include "npc.hpp"

class CCell
{
public:
    char texture;
private:
    enum state
    {
        OCCUPIED,
        UNBREAKABLE,
        DESTROYABLE
    };

    std::shared_ptr<CCharacter> occupiedBy;
public:
    CCell(char _c);
    ~CCell();
};
