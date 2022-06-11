#include "vigilante.hpp"

CVigilante::CVigilante(char _s) : CCharacter(_s)
{
    placedBomb = true;

    currBomb = nullptr;

    range = _START_RANGE;

    tTE = _START_TIME_TO_EXPLODE * _LONGER_TIME;

    hp = _START_HP;

    panicCnt = 0;

    characterType = VIGILANTE;

    for(int i = 0; i < _PANIC_ARRAY_SIZE; i++)
	    hist[i] = i;
}

bool CVigilante::onePlace()
{
    int first = hist[0];

    for(int i = 1; i < _PANIC_ARRAY_SIZE; i++)
    {
        if(first != hist[i])
            return false;
    }

    panicCnt = _PANIC_ARRAY_SIZE;

    return true;
}
std::shared_ptr<CWeapon> CVigilante::decideNextMove(char & _i, int playerAtCol, int playerAtLine,  std::vector<std::pair<int, int>> & _tA)
{
    if(currBomb != nullptr && currBomb->update())
    {
        _tA = currBomb->explode();

        currBomb = nullptr;
        placedBomb = true;
    }
    
    int dir = _INIT_DIR;
    int rndm = std::rand() % speed;

    if(onePlace() || panicCnt != 0)
    {
        dir = (std::rand() % speed);
        panicCnt--;
    }
    else
    {
        if(rndm == 0)
        {
            int rnd = std::rand() % 2;

            if(line != playerAtLine && rnd == 1)
            {
                if(line > playerAtLine)
                    dir = UP;
                else
                    dir = DOWN;
            }
            else if(column != playerAtCol)
            {
                if(column > playerAtCol)
                    dir = LEFT;
                else
                    dir = RIGHT;
            }
            else if(line != playerAtLine)
            {
                if(line > playerAtLine)
                    dir = UP;
                else
                    dir = DOWN;
            }
            else
            {
                if(column > playerAtCol)
                    dir = LEFT;
                else
                    dir = RIGHT;
            }
        }
    }

    switch(dir)
    {
        case 0:
            _i = _UP; // UP
            break;
        case 1:
            _i = _RIGHT; // RIGHT
            break;
        case 2:
            _i = _DOWN; // DOWN
            break;
        case 3:
            _i = _LEFT;
            break;
        case 4:
            return placeBomb();
        default:
            _i = _STAY;
    }
    return nullptr;
}

void CVigilante::change()
{
    return;
}

std::shared_ptr<CWeapon> CVigilante::placeBomb()
{
    if(placedBomb)
    {
        std::shared_ptr<CWeapon> _c;
        _c = std::make_shared<CWeapon>(range, tTE,line, column);
        currBomb = _c;
        placedBomb = 0;
        return _c;
    }   
    return nullptr;
}

const void CVigilante::draw(std::vector<std::vector<int>> & toBeDisplayed)
{
    int _ib = 0;
    int blocks[]
    {
        COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,
        COLOR_WHITE, COLOR_CYAN, COLOR_CYAN,
        COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,
        COLOR_WHITE, COLOR_BLUE, COLOR_WHITE,
        COLOR_WHITE, COLOR_BLUE, COLOR_WHITE
    };

    for(int renderLine = 0; renderLine < _POSITION_HEIGHT; renderLine++)
    {
        for(int renderColumn = 0; renderColumn < _POSITION_WIDTH; renderColumn++)
        {
            toBeDisplayed.at((line * _POSITION_HEIGHT) + renderLine).push_back(blocks[_ib]);
            _ib++;
        }
    }

}
