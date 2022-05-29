#include "cell.hpp"

CCell::CCell(char _c)
{
    texture = _c;

    if(_c == '1')
    {
        occupiedBy = std::make_shared<CPlayer>(_c);
        currState = OCCUPIED;
    }
    else
    {
        occupiedBy = nullptr;

        if(_c == '@') currState = DESTROYABLE;
        else if (_c == ' ') currState = FREE;
        else currState = UNBREAKABLE;
    }
}

CCell::~CCell()
{
    
}