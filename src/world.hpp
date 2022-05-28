#pragma once

#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ncurses.h>

#include "cell.hpp"

//#define RAND_MAX 1

class CWorld
{
public:
    std::vector<std::vector<CCell>> worldMap;
    
    CWorld(WINDOW * _w);
    CWorld(int sourceFile, WINDOW * _w);

    void update(char _i);
    
    ~CWorld();
};
