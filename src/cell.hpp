#pragma once

#include "character.hpp"

class CCell
{
private:
    enum state
    {
        OCCUPIED,
        UNBREAKABLE,
        DESTROYABLE
    };
    CCharacter * occupiedBy;
public:
    CCell(/* args */);
    ~CCell();
};
