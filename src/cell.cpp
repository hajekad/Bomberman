#include "cell.hpp"

CCell::CCell(char _c)
{
    texture = _c;

    if(isalpha(_c)) occupiedBy = std::make_shared<CPlayer>(_c);
}

CCell::~CCell()
{
    
}