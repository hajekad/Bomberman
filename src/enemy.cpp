#include "enemy.hpp"

CEnemy::CEnemy(char _s) : CCharacter(_s)
{
    srand( (unsigned)time(NULL) );
    //int type = std::rand() % 5;

    hp = 15;
}

void CEnemy::attack(CCharacter & toAttack)
{
    
}

void CEnemy::decideNextMove(char & _i, int playerAtCol, int playerAtLine)
{
    //srand( time() );

    int rndm = std::rand() % speed;

    if(rndm == 0)
    {
        int dir = 5;

        int rnd = std::rand() % 2;

        if(line != playerAtLine && rnd == 1)
        {
            if(line > playerAtLine) dir = 0;
            else dir = 2;
        }
        else if(column != playerAtCol)
        {
            if(column > playerAtCol) dir = 3;
            else dir = 1;
        }
        else if(line != playerAtLine)
        {
            if(line > playerAtLine) dir = 0;
            else dir = 2;
        }
        else
        {
            if(column > playerAtCol) dir = 3;
            else dir = 1;
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
}

void CEnemy::receiveDmg(int _d)
{

}
