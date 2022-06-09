#include "player.hpp"

CPlayer::CPlayer(char _s) : CCharacter(_s)
{
    damage = 1;
    speed = 1;
    placedBomb = 1;
    currBomb = nullptr;
    range = 2;
    tTE = 4;
}

std::shared_ptr<CWeapon> CPlayer::placeBomb()
{
    if(placedBomb)
    {
        std::cerr << "BOMB\n";
        std::shared_ptr<CWeapon> _c;
        _c = std::make_shared<CWeapon>(range, tTE,line, column);
        currBomb = _c;
        placedBomb = 0;
        return _c;
    }   
    return nullptr;
}

void CPlayer::changeRange(int _r)
{
    range += _r;
}

void CPlayer::changeTTE()
{
    if(tTE != 1) tTE--;
}

std::shared_ptr<CWeapon> CPlayer::decideNextMove(char & _i, int playerAtCol, int playerAtLine,  std::vector<std::pair<int, int>> & _tA)
{
    if(((_i == 'o') || (_i == 'e')))
        return placeBomb();

    if(currBomb != nullptr && currBomb->update())
    {
        _tA = currBomb->explode();

        currBomb = nullptr;
        placedBomb = 1;
    }

    if(second)
    {
        switch(_i)
        {
            case 'i': _i = 'w'; break; // UP
            case 'l': _i = 'd'; break; // RIGHT
            case 'k': _i = 's'; break; // DOWN
            case 'j': _i = 'a'; break; // LEFT

            default: _i = 'H'; break;
        }
    }

   return nullptr;     
}

void CPlayer::change()
{
    int rand = std::rand() % 3;

    if(rand) changeRange(rand);
    else changeTTE();
}