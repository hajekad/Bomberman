#include "character.hpp"

CCharacter::CCharacter(char _s)
{
    skin = _s;

    isalpha(_s) ? characterType = PLAYER : characterType = NPC;

    if(characterType == NPC && _s != 'N') characterType = ENEMY;
}

CCharacter::~CCharacter()
{
}