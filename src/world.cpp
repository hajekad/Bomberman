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
                std::cerr << "will erase?\n" << j->get()->line << " " << i->first << std::endl << j->get()->column << " " << i->second << std::endl;
                if((j->get()->line == i->first) && (j->get()->column == i->second))
                {
                    std::cerr << "erase\n"; 
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
    if(characters.begin()->get()->characterType != PLAYER) return 1;

    CPlayer * player = (CPlayer *) characters.begin()->get();
    auto tmp = characters.begin();
    tmp++;
    CPlayer * playerTwo = (CPlayer *) tmp->get();

    if(_i == 'e')
        player->placeBomb(worldMap.at(player->line).at(player->column));

    if(_i == 'o' && playerCnt > 1)
        playerTwo->placeBomb(worldMap.at(playerTwo->line).at(playerTwo->column));

    int k = 0;

    if(player->currBomb != nullptr) if(player->currBomb->update())
    {
        std::vector<std::pair<int, int>> toAttack = player->currBomb->explode(int(worldMap.size()), int(worldMap.at(1).size()));

        destroy(toAttack);

        worldMap.at(player->currBomb->line).at(player->currBomb->column).bomb = nullptr;
        worldMap.at(player->currBomb->line).at(player->currBomb->column).currState = FREE;

        player->currBomb = nullptr;
        player->placedBomb = 1;
    }

    if(playerCnt > 1) if(playerTwo->currBomb != nullptr) if(playerTwo->currBomb->update())
    {
        std::vector<std::pair<int, int>> toAttackTwo = playerTwo->currBomb->explode(int(worldMap.size()), int(worldMap.at(1).size()));

        destroy(toAttackTwo);

        worldMap.at(playerTwo->currBomb->line).at(playerTwo->currBomb->column).bomb = nullptr;
        worldMap.at(playerTwo->currBomb->line).at(playerTwo->currBomb->column).currState = FREE;

        playerTwo->currBomb = nullptr;
        playerTwo->placedBomb = 1;
    } 


    int playerAtLine = player->line;
    int playerAtCol = player->column;

    int playerTwoAtLine = playerTwo->line;
    int playerTwoAtCol = playerTwo->column;

    hasPlayer = 0;
    hasEnemy = 0;
    playerCnt = 0;
    int loopifier = 0;

    for(auto _ic = characters.begin(); _ic != characters.end(); _ic++)
    {
        loopifier++;
        if(_ic->get()->characterType == PLAYER)
        {
            hasPlayer = 1;
            playerCnt++;
        }
        if(_ic->get()->characterType == ENEMY) hasEnemy = 1;
        int newLine = (*_ic).get()->line;
        int newCol = _ic->get()->column;
        k++;

        _ic->get()->decideNextMove(_i, playerAtCol, playerAtLine);

        if(_ic->get()->characterType == PLAYER && loopifier == 2)
        {
            switch(_i)
            {
                case 'i': newLine--; break;
                case 'j': newCol--; break;
                case 'k': newLine++; break;
                case 'l': newCol++; break;

                default: break;
            }
        }
        else
        {
            switch(_i)
            {
                case 'w': newLine--; break;
                case 'a': newCol--; break;
                case 's': newLine++; break;
                case 'd': newCol++; break;

                default: break;
            }
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

        //if(_ic->get()->characterType == PLAYER) _i = 'H';
    }

    if(!hasPlayer) return 1;

    //if(!hasEnemy) return 2;
    
    return 0;
}

CWorld::CWorld(std::string fileName, WINDOW * _w)
{

    std::ifstream fileStream;
    fileStream.open(fileName);
    std::vector<CCell> currLine;

    std::string line;

    playerCnt = 0;
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
                if(characters.back().get()->characterType == PLAYER) playerCnt++;
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

{
}
*/
