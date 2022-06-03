#pragma once

#include <vector>
#include <utility>
#include <chrono>
#include <thread>

//#include "world.hpp"

//class CWorld;

class CWeapon
{
public:
    int column;
    int line;

private:
    int range;
    std::chrono::time_point<std::chrono::system_clock> timeToExplode;

public:
    CWeapon(int _r, int _t, int _l, int _c);

    void change(int _r, int _t);
    
    bool update();

   std::vector<std::pair<int, int>> explode(int _lC, int _cC);
};
