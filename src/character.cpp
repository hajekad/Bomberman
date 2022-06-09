#include "character.hpp"

CCharacter::CCharacter(char _s)
{
    skin = _s;
    second = 0;
    if(_s == 'P') characterType = PLAYER;
    else if(_s == 'E') characterType = ENEMY;

    speed = std::rand() % 5 + 4;

    stayed = false;
    iH = 0;
    score = 0;

}

CCharacter::~CCharacter()
{
}