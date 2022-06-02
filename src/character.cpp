#include "character.hpp"

CCharacter::CCharacter(char _s)
{
    skin = _s;

    isalpha(_s) ? characterType = PLAYER : characterType = NPC;

    if(characterType == NPC && _s != 'N') characterType = ENEMY;

    speed = std::rand() % 5 + 4;

    stayed = false;
    iH = 0;
}

CCharacter::~CCharacter()
{
}