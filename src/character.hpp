#pragma once

#include "player.hpp"
#include "npc.hpp"
#include "enemy.hpp"

class CCharacter
{
private:
    enum characterType
    {
        PLAYER,
        NPC,
        ENEMY
    }; 

public:
    CCharacter();
    ~CCharacter();

    virtual void move();
    virtual void perish();
};