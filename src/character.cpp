#include "character.hpp"

CCharacter::CCharacter(char _s)
{
    skin = _s;
    second = 0;
    if(_s == _PLAYER) characterType = PLAYER;
    else if(_s == _ENEMY) characterType = ENEMY;

    speed = std::rand() % _MAX_SPEED_DIFF + _MAX_SPEED;

    stayed = false;
    iH = 0;
    score = 0;
    alive = true;

}

CCharacter::~CCharacter()
{
}