#include "enemy.hpp"

CEnemy::CEnemy(char _s) : CCharacter(_s)
{
    hp = 15;

    panicCnt = 0;

    characterType = ENEMY;
}

bool CEnemy::onePlace()
{
    int first = hist[0];

    for(int i = 1; i < 5; i++)
    {
        if(first != hist[i])
            return 0;
    }

    panicCnt = 5;

    return 1;
}

void CEnemy::decideNextMove(char & _i, int playerAtCol, int playerAtLine)
{
    int dir = 5;
    int rndm = std::rand() % speed;

    if(onePlace() || panicCnt != 0)
    {
        dir = std::rand() % (speed + 7);
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
                    dir = 0;
                else
                    dir = 2;
            }
            else if(column != playerAtCol)
            {
                if(column > playerAtCol)
                    dir = 3;
                else
                    dir = 1;
            }
            else if(line != playerAtLine)
            {
                if(line > playerAtLine)
                    dir = 0;
                else
                    dir = 2;
            }
            else
            {
                if(column > playerAtCol)
                    dir = 3;
                else
                    dir = 1;
            }
        }
    }

    switch(dir)
    {
        case 0:
            _i = 'w';
            break;
        case 1:
            _i = 'd';
            break;
        case 2:
            _i = 's';
            break;
        case 3:
            _i = 'a';
            break;
        default:
            _i = 'H';
    }
}
