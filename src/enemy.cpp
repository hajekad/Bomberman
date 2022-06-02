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
    //srand( time() );

    int rndm = std::rand() % 6;

    if(rndm == 0)
    {
        int dir = std::rand() % 4;

        //std::cerr << "Direction: " << dir << std::endl;

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
