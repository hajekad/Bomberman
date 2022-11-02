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
    if(std::chrono::system_clock::now() > timeToExplode) return true;
    
    return false;
}

std::vector<std::pair<int, int>> CWeapon::explode()
{
    std::vector<std::pair<int, int>> ret;

    int dirCnt, _u, _d, _l, _r;
    dirCnt = _u = _d = _l = _r = 0;

    ret.push_back(std::make_pair(line, column));

    for(int i = 1; i < range; i++)
    {
        ret.push_back(std::make_pair(line - i, column));
        ret.push_back(std::make_pair(line + i, column));
        ret.push_back(std::make_pair(line, column - i));
        ret.push_back(std::make_pair(line, column + i));
    }
    dirCnt = _DIRECTIONS_IN_EXISTENCE;
    ret.push_back(std::make_pair(dirCnt, dirCnt));

    return ret;
}
