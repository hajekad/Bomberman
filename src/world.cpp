#include "world.hpp"

void CWorld::destroy(std::vector<std::pair<int, int>> & _d)
{
    for(auto i = _d.begin(); i != _d.end(); i++)
    {
        CCell * _c = &(worldMap.at(i->first).at(i->second));
        
        if(_c->currState == OCCUPIED)
        {
            for(auto j = characters.begin(); j != characters.end(); j++)
            {
                if(_c->occupiedBy == *j && _c->occupiedBy.get()->characterType != PLAYER)
                {
                    characters.erase(j);
                    break;
                }
            }

            _c->currState = FREE;
            _c->occupiedBy = nullptr;
            _c->texture = ' ';
        }
        else if(_c->currState == DESTROYABLE)
        {
            _c->currState = FREE;
            _c->texture = ' ';
        }
    }
}

int CWorld::update(char _i)
{
    if(_i == 'e')
    {
        CPlayer * player = (CPlayer *) characters.begin()->get();
        player->placeBomb(worldMap.at(player->line).at(player->column));
    }

    int k = 0;

    if(characters.begin()->get()->characterType != PLAYER) return 1; 

    CPlayer * player = (CPlayer *) characters.begin()->get();

    if(player->currBomb != nullptr) if(player->currBomb->update())
    {
        std::vector<std::pair<int, int>> toAttack = player->currBomb->explode(int(worldMap.size()), int(worldMap.at(1).size()));

        destroy(toAttack);

        worldMap.at(player->currBomb->line).at(player->currBomb->column).bomb = nullptr;
        worldMap.at(player->currBomb->line).at(player->currBomb->column).currState = FREE;

        player->currBomb = nullptr;
        player->placedBomb = 1;
    }

    int playerAtLine = characters.begin()->get()->line;
    int playerAtCol = characters.begin()->get()->column;

    hasPlayer = 0;

    for(auto _ic = characters.begin(); _ic != characters.end(); _ic++)
    {
        if(_ic->get()->characterType == PLAYER) hasPlayer = 1;
        int newLine = (*_ic).get()->line;
        int newCol = _ic->get()->column;
        k++;

        _ic->get()->decideNextMove(_i, playerAtCol, playerAtLine);

        switch(_i)
        {
            case 'w': newLine--; break;
            case 'a': newCol--; break;
            case 's': newLine++; break;
            case 'd': newCol++; break;

            default: break;
        }

        _ic->get()->hist[(_ic->get()->iH)] = newCol + newLine;
        (_ic->get()->iH)++;
        (_ic->get()->iH) %= 5;

        if((worldMap.at(newLine).at(newCol).currState == FREE) && ((newLine != _ic->get()->line) || newCol != _ic->get()->column))
        {
            worldMap.at(newLine).at(newCol).occupiedBy = *_ic;
            worldMap.at(newLine).at(newCol).texture = _ic->get()->skin;
            worldMap.at(newLine).at(newCol).currState = OCCUPIED;

            worldMap.at(_ic->get()->line).at(_ic->get()->column).occupiedBy = nullptr;
            worldMap.at(_ic->get()->line).at(_ic->get()->column).texture = ' ';
            worldMap.at(_ic->get()->line).at(_ic->get()->column).currState = FREE;

            _ic->get()->line = newLine;
            _ic->get()->column = newCol;
        }
        else if((worldMap.at(newLine).at(newCol).currState == OCCUPIED)
                && ((newLine != _ic->get()->line) || newCol != _ic->get()->column)
                && (worldMap.at(newLine).at(newCol).occupiedBy.get()->characterType == PLAYER)) return 1;

        if(_ic->get()->characterType == PLAYER) _i = 'H';
    }

    if(!hasPlayer) return 1;
    
    return 0;
}

CWorld::CWorld(std::string fileName, WINDOW * _w)
{

    std::ifstream fileStream;
    fileStream.open(fileName);
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

/*
CWorld::~CWorld()
{
}
*/
