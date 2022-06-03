#include "cell.hpp"

CCell::CCell(char _c)
{
    texture = _c;

    bomb = nullptr;

    if(_c == 'P')
    {
        occupiedBy = std::make_shared<CPlayer>(_c);
        currState = OCCUPIED;
    }
    else if(_c == 'E')
    {
        occupiedBy = std::make_shared<CEnemy>(_c);
        currState = OCCUPIED;
    }
    else if(_c == 'N')
    {
        currState = FREE;
    }
    else
    {
        occupiedBy = nullptr;

        if(_c == '@')
            currState = DESTROYABLE;
        else if (_c == ' ')
            currState = FREE;
        else
            currState = UNBREAKABLE;
    }
}

CCell::~CCell()
{
    if(occupiedBy.use_count() == 0)
        delete occupiedBy.get();
        
    if(bomb.use_count() == 0)
        delete bomb.get();
}