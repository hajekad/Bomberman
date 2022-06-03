#include "weapon.hpp"

CWeapon::CWeapon(int _r, int _t, int _l, int _c)
{
    range = _r;
    timeToExplode = std::chrono::system_clock::now() + std::chrono::seconds(_t);
    line = _l;
    column = _c;
}

void CWeapon::change(int _r, int _t)
{

}

bool CWeapon::update()
{
    if(std::chrono::system_clock::now() > timeToExplode) return 1;
    return 0;
}
