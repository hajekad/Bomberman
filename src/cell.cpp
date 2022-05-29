#include "cell.hpp"

CCell::CCell(char _c)
{
    texture = _c;

    if(isalpha(_c))
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