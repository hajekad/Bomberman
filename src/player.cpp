#include "player.hpp"

CPlayer::CPlayer(char _s) : CCharacter(_s)
{
    damage = 1;
    speed = 1;
    placedBomb = 1;
    currBomb = nullptr;
    score = 0;
    range = 1;
    tTE = 4;
}

void CPlayer::placeBomb(CCell & _c)
{
    if(placedBomb)
    {
        _c.currState = BOMB;
        _c.bomb = std::make_shared<CWeapon>(range, tTE,line, column);
        currBomb = _c.bomb;
        placedBomb = 0;
    }
}

void CPlayer::changeRange(int _r)
{
    range += _r;
}

void CPlayer::changeTTE()
{
    if(tTE != 1) tTE--;
}

void CPlayer::decideNextMove(char & _i, int playerAtCol, int playerAtLine)
{
    return;
}