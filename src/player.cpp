#include "player.hpp"

CPlayer::CPlayer(char _s) : CCharacter(_s)
{
    damage = 1;
    speed = 1;
    placedBomb = 1;
    currBomb = nullptr;
    score = 0;
}

void CPlayer::placeBomb(CCell & _c)
{
    if(placedBomb)
    {
        _c.currState = BOMB;
        _c.bomb = std::make_shared<CWeapon>(5,2,line, column);
        currBomb = _c.bomb;
        placedBomb = 0;
    }
}

void CPlayer::useSecond()
{

}

void CPlayer::decideNextMove(char & _i, int playerAtCol, int playerAtLine)
{
    return;
}