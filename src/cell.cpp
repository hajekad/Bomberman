#include "cell.hpp"

CCell::CCell(char _c)
{
    texture = _c;

    bomb = nullptr;

    hasBonus = false;

    if(_c == _PLAYER)
    {
        occupiedBy = std::make_shared<CPlayer>(_c);
        currState = OCCUPIED;
    }
    else if(_c == _ENEMY)
    {
        occupiedBy = std::make_shared<CEnemy>(_c);
        currState = OCCUPIED;
    }
    else if(_c == _VIGILANTE)
    {
        occupiedBy = std::make_shared<CVigilante>(_c);
        currState = OCCUPIED;
    }
    else if(_c == _BONUS)
    {
        currState = FREE;
        hasBonus = true;
    }
    else
    {
        occupiedBy = nullptr;

        if(_c == _DESTROYABLE)
            currState = DESTROYABLE;
        else if (_c == _FREE)
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