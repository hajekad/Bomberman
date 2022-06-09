#pragma once

#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <ncurses.h>

#include "cell.hpp"
//#include "weapon.hpp"

//class CWeapon;

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define _MORE_SCORE 100

class CWorld
{
private:
    int playerCnt; /** *@brief count of players on the current map */
    
    bool hasPlayer; /** *@brief true if a player is present on this map */
    
    bool hasEnemy; /** *@brief true if a enemy is on this map */
    
    int scorePO; /** *@brief score of player one */
    
    int scorePT; /** *@brief score of player two */
    
    std::shared_ptr<CCharacter> _p1; /** *@brief player 1 */
    
    std::shared_ptr<CCharacter> _p2; /** *@brief player 2 */

    void parseD(std::vector<std::pair<int, int>> & _d);

public:
    int highScore;

    bool isnum(char _a);

    std::vector<std::vector<CCell>> worldMap; /** *@brief map built from cells */
    
    std::vector<std::shared_ptr<CCharacter>> characters; /** *@brief all characters that are still alive */
    
    CWorld(std::string fileName, WINDOW * _w);

    /**
     * @brief influences state of cells with coordinates from _d
     * 
     * @param _d vector of all influenced cells
     * @param _p owner of the exploding bomb
     */
    void destroy(std::vector<std::pair<int, int>> & _d, std::shared_ptr<CCharacter> _p);

    /**
     * @brief updates the state of map in time, detonates bomb and decides the next move of the game
     * 
     * @param _i input from player
     * @return int final high score or 1
     */
    int update(char _i);
};
