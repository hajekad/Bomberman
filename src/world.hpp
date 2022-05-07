#pragma once

#include <vector>
#include "cell.hpp"

class CWorld
{
private:
    std::vector<std::vector<CCell>> worlMap;
public:
    CWorld(const char * sourceFile);
    ~CWorld();
};
