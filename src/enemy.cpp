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

void CEnemy::decideNextMove(char & _i)
{
    srand( (unsigned)time(NULL) );

    int rndm = std::rand() % 15;

    if(rndm == 0)
    {
        int dir = std::rand() % 4;

        switch(dir)
        {
            case 0:
                _i = 'w';
                break;

            case 1:
                _i = 'w';
                break;

            case 2:
                _i = 'w';
                break;

            case 3:
                _i = 'w';
                break;

            default:
                _i = 'H';
        }
    }
}

void CEnemy::receiveDmg(int _d)
{

}
