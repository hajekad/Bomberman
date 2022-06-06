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

//#define RAND_MAX 1

class CWorld
{
private:
    int playerCnt;
    bool hasPlayer;
    bool hasEnemy;
    int scorePO;
    int scorePT;
    std::shared_ptr<CCharacter> _p1;
    std::shared_ptr<CCharacter> _p2;

public:
    std::vector<std::vector<CCell>> worldMap;
    
    std::vector<std::shared_ptr<CCharacter>> characters;
    
    CWorld(std::string fileName, WINDOW * _w);

    void destroy(std::vector<std::pair<int, int>> & _d, CPlayer * _p);

    int update(char _i);
    
    //~CWorld();
};
