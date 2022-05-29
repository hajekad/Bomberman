#include "world.hpp"

CWorld::CWorld(WINDOW * _w)
{
    CWorld( std::rand() % 2, _w);
}

void CWorld::update(char _i)
{
    switch(_i)
    {
        case 'w': break;

        case 'a': break;

        case 's': break;

        case 'd': break;

        default:  return;
    }

    std::shared_ptr<CCharacter> player;
    int col = 0;
    int line = 0;
    bool esc = 0;
    std::vector<CCell>::iterator prev;

    auto it = worldMap.begin();
    it++;

    for(; it != worldMap.end(); it++)
    {
        line++;

        col = 0;
        auto jt = it->begin();
        jt++;
        for(; jt != it->end(); jt++)
        {
            col++;
            if(jt->texture == '1')
            {
                player = jt->occupiedBy;
                prev = jt;
                esc = 1;
                break;
            }
        }
        if(esc == 1) break;
    }

    switch(_i)
    {
        case 'w':
            line--;
            break;

        case 'a':
            col--;
            break;

        case 's':
            line++;
            break;

        case 'd':
            col++;
            break;

        default:
            return;
    }

    if(esc && (worldMap.at(line).at(col).currState == FREE))
    {
        worldMap.at(line).at(col).occupiedBy = player;
        worldMap.at(line).at(col).texture = '1';    
        prev->occupiedBy = nullptr;
        prev->texture = ' ';
    }
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