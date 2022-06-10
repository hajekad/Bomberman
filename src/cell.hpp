#pragma once

#include <memory>

#include "player.hpp"
#include "enemy.hpp"
#include "vigilante.hpp"

#define _PLAYER 'P'
#define _ENEMY 'E'
#define _VIGILANTE 'V'
#define _BONUS 'B'
#define _DESTROYABLE '@'
#define _FREE ' '

class CPlayer;

enum state
{
    FREE,
    OCCUPIED,
    UNBREAKABLE,
    DESTROYABLE,
    BOMB
};

class CCell
{
public:
    bool hasBonus; /** *@brief hasBonus determines if bonus item is present */
    
    char texture;  /** *@brief current texture of Cell */
    
    state currState; /** *@brief current state of this Cell */

    std::shared_ptr<CCharacter> occupiedBy; /** *@brief a cell can be occupied by a character */
    
    std::shared_ptr<CWeapon> bomb; /** *@brief a bomb can be placed on a cell */
    
    /**
     * @param _c will be set as texture
     * @return no return value
     */
    CCell(char _c);
    ~CCell();
};
