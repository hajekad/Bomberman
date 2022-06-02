#include "world.hpp"

CWorld::CWorld(WINDOW * _w)
{
    CWorld( std::rand() % 2, _w);
}

void CWorld::update(char _i)
{
    //std::cerr << "update" << std::endl;

    int k = 0;
    for(auto _ic = characters.begin(); _ic != characters.end(); _ic++)
    {
        k++;
        //std::cerr << k << std::endl;
        int newLine = (*_ic).get()->line;
        int newCol = _ic->get()->column;

        _ic->get()->decideNextMove(_i);

        switch(_i)
        {
            case 'w': newLine--; break;
            case 'a': newCol--; break;
            case 's': newLine++; break;
            case 'd': newCol++; break;

            default: break;
        }

        if((worldMap.at(newLine).at(newCol).currState == FREE) && ((newLine != _ic->get()->line) || newCol != _ic->get()->column))
        {
            worldMap.at(newLine).at(newCol).occupiedBy = *_ic;
            worldMap.at(newLine).at(newCol).texture = _ic->get()->skin;

            worldMap.at(_ic->get()->line).at(_ic->get()->column).occupiedBy = nullptr;
            worldMap.at(_ic->get()->line).at(_ic->get()->column).texture = ' ';

            _ic->get()->line = newLine;
            _ic->get()->column = newCol;
        }
        if(_ic->get()->characterType == PLAYER) _i = 'H';
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

    int _l = 0;
    int help = 0;
    while(getline(fileStream, line))
    {
        auto end = line.end();
        auto copy = end;
        copy--;

        int _c = 0;
        for(auto i = line.begin(); i != end; i++)
        {
            foo++;

            CCell currCell = CCell(*i);

            if(currCell.currState == OCCUPIED)
            {
                currCell.occupiedBy->line = _l;
                currCell.occupiedBy->column = _c;
                characters.push_back(currCell.occupiedBy);
                help++;
                //std::cerr <<"HELP"<< help << std::endl;
            }
            currLine.push_back(currCell);
            if(i == copy) worldMap.push_back(currLine);
            _c++;
        }
        line.clear();
        currLine.clear();
        _l++;
    }
}


CWorld::~CWorld()
{
}