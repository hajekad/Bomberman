#include "enemy.hpp"

CEnemy::CEnemy(char _s) : CCharacter(_s)
{
    hp = _START_HP;

    panicCnt = 0;

    characterType = ENEMY;

    for(int i = 0; i < _PANIC_ARRAY_SIZE; i++)
	hist[i] = i;
}

bool CEnemy::onePlace()
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
std::shared_ptr<CWeapon> CEnemy::decideNextMove(char & _i, int playerAtCol, int playerAtLine,  std::vector<std::pair<int, int>> & _tA)
{
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
        default:
            _i = _STAY;
    }
    return nullptr;
}

void CEnemy::change()
{
    if(speed > _MAX_SPEED) speed--; // fastest playable speed
}

const void CEnemy::draw(std::vector<std::vector<int>> & toBeDisplayed)
{
    int _ib = 0;
    int blocks[]
    {
        COLOR_RED, COLOR_RED,  COLOR_RED,
        COLOR_RED, COLOR_CYAN, COLOR_CYAN,
        COLOR_RED, COLOR_RED,  COLOR_RED,
        COLOR_RED, COLOR_BLUE, COLOR_RED,
        COLOR_RED, COLOR_BLUE, COLOR_RED
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
