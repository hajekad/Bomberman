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
        switch (cont % _DIRECTIONS_IN_EXISTENCE)
        {
            case UP:
                _u.push_back(*i);
                break;
            case RIGHT:
                _r.push_back(*i);
                break;
            case DOWN:
                _do.push_back(*i);
                break;
            case LEFT:
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
    parseD(_d);
    std::vector<std::vector<std::shared_ptr<CCharacter>>::iterator> toDelete;

    for(auto i = _d.begin(); i != (_d.end()); i++)
    {
        if(i->first > 0 && size_t(i->first) < worldMap.size() && i->second > 0 && size_t(i->second) < worldMap.at(1).size())
        {
            CCell * _c = &(worldMap.at(i->first).at(i->second));
            worldMap.at(i->first).at(i->second).bomb = nullptr;

            if(_c->currState == OCCUPIED || (_c->currState == BOMB && _c->occupiedBy != nullptr))
            {
                if(_p != nullptr) _p.get()->score += _MORE_SCORE;

                for(auto j = characters.begin(); j != characters.end(); j++)
                {
                    if((j->get()->line == i->first) && (j->get()->column == i->second))
                    {
                        //std::vector<std::pair<int, int>> toAttackTwo;
                        //destroy(toAttackTwo, *j);
                        j->get()->alive = false;
                        //toDelete.push_back(j);
                        break;
                    }
                }

                if(_c->currState != BOMB) _c->currState = FREE;
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

    //for(auto i : toDelete)
    //    characters.erase(i);
}

int CWorld::update(char _i)
{
    if(characters.begin()->get()->characterType != PLAYER) return 1;

    CCharacter * player = characters.begin()->get();
    auto tmp = characters.begin();
    tmp++;
    CCharacter * playerTwo = tmp->get();

    int playerAtLine = player->line;
    int playerAtCol = player->column;

    int playerTwoAtLine = playerTwo->line;
    int playerTwoAtCol = playerTwo->column;

    ///nulls the control parameters of the game state
    hasPlayer = false;
    hasEnemy = false;
    playerCnt = 0;
    int loopifier = 0;

    ///update all the characters alive and mocve them around
    for(auto _ic = characters.begin(); _ic != characters.end(); _ic++)
    {
        loopifier++;
        if(_ic->get()->characterType == PLAYER)
        {
            hasPlayer = true;
            playerCnt++;
        }
        if(_ic->get()->characterType == ENEMY || _ic->get()->characterType == VIGILANTE) hasEnemy = true;

        int newLine = (*_ic).get()->line;
        int newCol = _ic->get()->column;

        std::vector<std::pair<int, int>> toAttack;

        /// decides the desired direction to move to or places a bomb to a currently occupied cell
        std::shared_ptr<CWeapon> newBomb = nullptr;
        if(loopifier % 2 && playerCnt > 1)
            newBomb = _ic->get()->decideNextMove(_i, playerTwoAtCol, playerTwoAtLine, toAttack);
        else
            newBomb = _ic->get()->decideNextMove(_i, playerAtCol, playerAtLine, toAttack);

        if(!toAttack.empty()) destroy(toAttack, *_ic);

        if(_ic->get()->alive)
        {
            ///plants the bomb
            if(newBomb != nullptr)
            {
                worldMap.at(_ic->get()->line).at(_ic->get()->column).bomb = newBomb;
                worldMap.at(_ic->get()->line).at(_ic->get()->column).currState = BOMB;
            }

            ///provides new desired coordinates
            switch(_i)
            {
                case _UP: newLine--; break;
                case _LEFT: newCol--; break;
                case _DOWN: newLine++; break;
                case _RIGHT: newCol++; break;

                default: break;
            }

            ///moves the history iterator
            _ic->get()->hist[(_ic->get()->iH)] = newCol + newLine;
            (_ic->get()->iH)++;
            (_ic->get()->iH) %= _PANIC_ARRAY_SIZE;

            ///actually moves the character and updates the world map
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

                if(worldMap.at(newLine).at(newCol).hasBonus)
                {
                    worldMap.at(newLine).at(newCol).hasBonus = 0;
                    worldMap.at(newLine).at(newCol).texture = _FREE;

                    _ic->get()->change();
                }
            }
            else if((worldMap.at(newLine).at(newCol).currState == OCCUPIED)
                    && ((newLine != _ic->get()->line) || newCol != _ic->get()->column)
                    && (worldMap.at(newLine).at(newCol).occupiedBy.get()->characterType == PLAYER)) return 1; // player bumped into a living thing and died
        }
        else
        {
            auto copy = _ic;
            _ic--;
            characters.erase(copy);
        }
    }

    ///returns to menu
    if(!hasPlayer) return 1;

    ///returns the winning score
    if(!hasEnemy)
    {
        CCharacter * _o1 = _p1.get();
        if(_p2.get() != nullptr)
        {
            CCharacter * _o2 = _p2.get();
    
    
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
    if(_a >= '0' && _a <= '9') return true;
    return false;
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
        _p2.get()->second = true;
    }
}
