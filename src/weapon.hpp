#pragma once

#include <vector>
#include <utility>
#include <chrono>
#include <iostream>
#include <thread>

//#include "world.hpp"

//class CWorld;

#define _DIRECTIONS_IN_EXISTENCE 4

class CWeapon
{
public:
    int column; /** *@brief column where the bomb is placed */
    int line;   /** *@brief line where the bomb is placed */

private:
    int range; /** *@brief range to destroy */
    std::chrono::time_point<std::chrono::system_clock> timeToExplode;

public:
    CWeapon(int _r, int _t, int _l, int _c);

    /**
     * @brief changes members of this
     * 
     * @param _r as for range 
     * @param _t as for time
     */
    void change(int _r, int _t);
    
    /**
     * @brief shortens the time to explode of this
     * 
     * @return true if explodes
     * @return false if does not explode
     */
    bool update();

    /**
     * @brief picks the coordinates to be influenced by explosion
     * 
     * @param _lC line to exlode on
     * @param _cC column to explode on
     * @return std::vector<std::pair<int, int>> for destroyed cells 
     */
    std::vector<std::pair<int, int>> explode();
};
