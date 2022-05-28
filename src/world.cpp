#include "world.hpp"

CWorld::CWorld(WINDOW * _w)
{
    CWorld( std::rand() % 2, _w);
}

void CWorld::update(char _i)
{
    
}

CWorld::CWorld(int sourceFile, WINDOW * _w)
{
/*
    std::stringstream workStream;
    
    char name[1];

    workStream << sourceFile;
    workStream >> name[0];
*/
    int foo = 0;
    std::ifstream fileStream;
    fileStream.open("map0.txt");
    std::vector<CCell> currLine;

    std::string line;
    
    while(getline(fileStream, line))
    {
        auto end = line.end();
        auto copy = end;
        copy--;

        for(auto i = line.begin(); i != end; i++)
        {
            foo++;
            currLine.push_back(CCell(*i));
            if(i == copy) worldMap.push_back(currLine);
        }
        line.clear();
        currLine.clear();
    }
}


CWorld::~CWorld()
{
}