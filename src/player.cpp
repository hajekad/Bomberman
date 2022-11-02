#include "player.hpp"

CPlayer::CPlayer(char _s) : CCharacter(_s)
{
    placedBomb = true;
    currBomb = nullptr;
    range = _START_RANGE;
    tTE = _START_TIME_TO_EXPLODE;
}

std::shared_ptr<CWeapon> CPlayer::placeBomb()
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

void CPlayer::changeRange(int _r)
{
    range += _r;
}

void CPlayer::changeTTE()
{
    if(tTE != 1) tTE--;
}

std::shared_ptr<CWeapon> CPlayer::decideNextMove(char & _i, int playerAtCol, int playerAtLine,  std::vector<std::pair<int, int>> & _tA)
{
    if(((_i == _BOMB_BUTTON_PLAYER_ONE) && second) || ((_i == _BOMB_BUTTON_PLAYER_TWO) && !second))
        return placeBomb();

    if(currBomb != nullptr && currBomb->update())
    {
        _tA = currBomb->explode();

        currBomb = nullptr;
        placedBomb = true;
    }

    if(second)
    {
        switch(_i)
        {
            case 'i': _i = _UP; break;
            case 'l': _i = _RIGHT; break;
            case 'k': _i = _DOWN; break;
            case 'j': _i = _LEFT; break;

            default: _i = _STAY; break;
        }
    }

   return nullptr;     
}

void CPlayer::change()
{
    int rand = std::rand() % _POSSIBLE_OUTCOMES;

    if(rand) changeRange(rand);
    else changeTTE();
}

const void CPlayer::draw(std::vector<std::vector<int>> & toBeDisplayed)
{
    int _ib = 0;
    int blocks[]
    {
        COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA,
        COLOR_CYAN,    COLOR_CYAN,    COLOR_MAGENTA,
        COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA,
        COLOR_MAGENTA, COLOR_BLUE, COLOR_MAGENTA,
        COLOR_MAGENTA, COLOR_BLUE, COLOR_MAGENTA
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
