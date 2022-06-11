#pragma once

#include <memory>

#include "character.hpp"
#include "weapon.hpp"
#include "cell.hpp"

#define _START_RANGE 2
#define _START_TIME_TO_EXPLODE 4
#define _BOMB_BUTTON_PLAYER_ONE 'o'
#define _BOMB_BUTTON_PLAYER_TWO 'e'
#define _POSSIBLE_OUTCOMES 3


class CCell;

class CPlayer : public CCharacter
{
public:
    std::shared_ptr<CWeapon> currBomb; /** *@brief pointer to a currently placed bomb */
    
    bool placedBomb; /** *@brief true if player can place a bomb */
    
private:    
    int tTE; /** *@brief time to explode, used for bomb */
    
    int range; /** *@brief range of players bombs */

    /**
     * @brief places a bomb to CCell _c
     * 
     * @param _c Cell to place a bomb to
     */
    std::shared_ptr<CWeapon> placeBomb();

public:
    CPlayer(char _s);

    /**
     * @brief changes range of bombs to range + _r
     * 
     * @param _r new additional range
     */
    void changeRange(int _r);

    /**
     * @brief substract 1 from tTE
     */
    void changeTTE(); 
        
    /**
     * @brief does nothing, is here because of parent class
     * 
     * @param _i 
     * @param playerAtCol 
     * @param playerAtLine 
     */
    std::shared_ptr<CWeapon> decideNextMove(char & _i, int playerAtCol, int playerAtLine,  std::vector<std::pair<int, int>> & _tA);

    void change();

    const void draw(std::vector<std::vector<int>> & toBeDisplayed);
};