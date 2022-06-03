#pragma once

#include <chrono>
#include <thread>

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
};
