#pragma once

#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ncurses.h>

#include "cell.hpp"
//#include "weapon.hpp"

//class CWeapon;

//#define RAND_MAX 1

class CWorld
{
private:
    bool hasPlayer;
public:
    std::vector<std::vector<CCell>> worldMap;
    
    std::vector<std::shared_ptr<CCharacter>> characters;
    
    CWorld(WINDOW * _w);

    CWorld(int sourceFile, WINDOW * _w);

    void destroy(std::vector<std::pair<int, int>> & _d);

    int update(char _i);
    
    //~CWorld();
};
