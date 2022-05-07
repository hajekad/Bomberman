#pragma once

#include "character.hpp"

class CNpc : public CCharacter
{
private:

public:
    void raisePlayerDamage();
    void raisePlayerSpeed();
    
    void move()override;
    void perish()override;
};