#include "world.hpp"

void CWorld::parseD(std::vector<std::pair<int, int>> & _d)
{
    auto i = _d.begin();
    auto tmp = i;
    int cont = 0;
    i++;
    std::vector<std::pair<int, int>> _u, _do, _l, _r;

    for(; i != (_d.end() - 1); i++)
    {
        switch (cont % 4)
        {
            case 0:
                _u.push_back(*i);
                break;
            case 1:
                _r.push_back(*i);
                break;
            case 2:
                _do.push_back(*i);
                break;
            case 3:
                _l.push_back(*i);
                break;
            default: break;
        }
        cont++;
    }

    _d.clear();
    _d.push_back(*tmp);

    for(auto i = _u.begin(); i != _u.end(); i++)
    {
        if(worldMap.at(i->first).at(i->second).currState == UNBREAKABLE) break;
        _d.push_back(*i);
    }
    for(auto i = _r.begin(); i != _r.end(); i++)
    {
        if(worldMap.at(i->first).at(i->second).currState == UNBREAKABLE) break;
        _d.push_back(*i);
    }
    for(auto i = _do.begin(); i != _do.end(); i++)
    {
        if(worldMap.at(i->first).at(i->second).currState == UNBREAKABLE) break;
        _d.push_back(*i);
    }
    for(auto i = _l.begin(); i != _l.end(); i++)
    {
        if(worldMap.at(i->first).at(i->second).currState == UNBREAKABLE) break;
        _d.push_back(*i);
    }
}

void CWorld::destroy(std::vector<std::pair<int, int>> & _d, std::shared_ptr<CCharacter> _p)
{
    std::cerr << "ultimATWE DESTRUCTION\n";
    parseD(_d);

    for(auto i = _d.begin(); i != (_d.end()); i++)
    {
        if(i->first > 0 && size_t(i->first) < worldMap.size() && i->second > 0 && size_t(i->second) < worldMap.at(1).size())
        {
            CCell * _c = &(worldMap.at(i->first).at(i->second));
            worldMap.at(i->first).at(i->second).bomb = nullptr;

            if(_c->currState == OCCUPIED || (_c->currState == BOMB && _c->occupiedBy != nullptr))
            {
                _p.get()->score += 100;
                for(auto j = characters.begin(); j != characters.end(); j++)
                {
                    if((j->get()->line == i->first) && (j->get()->column == i->second))
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
}

int CWorld::update(char _i)
{
    if(characters.begin()->get()->characterType != PLAYER) return 1;

    CCharacter * player = characters.begin()->get();
    auto tmp = characters.begin();
    tmp++;
    //CCharacter * playerTwo = (CCharacter *) tmp->get();

    int playerAtLine = player->line;
    int playerAtCol = player->column;
/*
    if(playerCnt > 1)
    {
        int playerTwoAtLine = playerTwo->line;
        int playerTwoAtCol = playerTwo->column;
    }
*/
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

        std::vector<std::pair<int, int>> toAttack;
        std::shared_ptr<CWeapon> newBomb = _ic->get()->decideNextMove(_i, playerAtCol, playerAtLine, toAttack);
        if(!toAttack.empty()) destroy(toAttack, *_ic);

        if(newBomb != nullptr)
        {
            std::cerr<<"C++standard xd\n";
            worldMap.at(_ic->get()->line).at(_ic->get()->column).bomb = newBomb;
            worldMap.at(_ic->get()->line).at(_ic->get()->column).currState = BOMB;
        }
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

            if(worldMap.at(newLine).at(newCol).hasBonus && _ic->get()->characterType == PLAYER)
            {
                CPlayer * _tp = (CPlayer *) _ic->get();
                worldMap.at(newLine).at(newCol).hasBonus = 0;
                worldMap.at(newLine).at(newCol).texture = ' ';
                int rand = std::rand() % 3;

                if(rand) _tp->changeRange(rand);
                else _tp->changeTTE();
            }
        }
        else if((worldMap.at(newLine).at(newCol).currState == OCCUPIED)
                && ((newLine != _ic->get()->line) || newCol != _ic->get()->column)
                && (worldMap.at(newLine).at(newCol).occupiedBy.get()->characterType == PLAYER)) return 1; // player bumped into a living thing and died
    }

    if(!hasPlayer) return 1;

    if(!hasEnemy)
    {
        CPlayer * _o1 = (CPlayer *) _p1.get();
        if(_p2.get() != nullptr)
        {
            CPlayer * _o2 = (CPlayer *) _p2.get();
    
    
            if(_o1->score == _o2->score)
                return scorePO;
            else if(_o1->score > _o2->score)
                return _o1->score + 1;
            else
                return _o2->score + 2;
        }
        else return _o1->score + 1; 
    }
    
    return 0;
}

bool CWorld::isnum(char _a)
{
    if(_a >= '0' && _a <= '9') return 1;
    return 0;
}

CWorld::CWorld(std::string fileName, WINDOW * _w)
{

    std::ifstream fileStream;
    fileStream.open(fileName);
    std::vector<CCell> currLine;

    scorePO = 0;
    scorePT = 0;

    std::string line;

    playerCnt = 0;
    int _l = 0;
    int help = 0;
    while(getline(fileStream, line))
    {
        if(isnum(*(line.begin())))
            highScore = std::stoi(line);
        else
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

    if(playerCnt == 1)
    {
        _p1 = *(characters.begin());
    }
    else if(playerCnt == 2)
    {
        _p1 = *(characters.begin());
        _p2 = *(++(characters.begin()));
        _p2.get()->second = 1;
    }
}
