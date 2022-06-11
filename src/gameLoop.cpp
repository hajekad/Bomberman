#include "gameLoop.hpp"

char CGameLoop::getInput(WINDOW * _w)
{
    cbreak();
    wtimeout(_w, 0);
    char ret;
    ret = wgetch(_w);
    flushinp();
    if(ret != ERR) return ret;
    return _STAY;
}

CGameLoop::CGameLoop(WINDOW * _w)
{
    renderer = std::make_unique<CAscii>(_w);

    currMap = nullptr;

    lowGraphics = true;
}

void CGameLoop::start(WINDOW * _w)
{
    wmove(_w, 1, getmaxx(_w)/2 - 4);
    wprintw(_w, "BOMBERMAN");
    wmove(_w, 2, getmaxx(_w)/2 - 13);
    wprintw(_w, "press any button to start");

    refresh();
    wrefresh(_w);

    running = true;
    inMenu = true;
    wgetch(_w);
}

void CGameLoop::mainThread(WINDOW * _w)
{
    std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();

    while(running)
    {
        if(inMenu)
        {
            gameMenu.render(_w);
            
            char tmp = 0;

            while(tmp == 0)
            {
                tmp = getInput(_w);
                if(tmp == _NEW_GAME)
                {
                    fileName.clear();
                    inMenu = 0;
                    fileName = "examples/map";
                    fileName +=  ((std::rand() % _MAP_COUNT) + '0');
                    fileName += ".txt";
                    if(currMap != nullptr) delete currMap;
                    currMap = new CWorld(fileName, _w);
                }
                else if(tmp == _LOAD_FILE)
                {
                    fileName.clear();
                    inMenu = 0;
                    fileName = gameMenu.pickLevel(_w);
                    if(currMap != nullptr) delete currMap;
                    currMap = new CWorld(fileName, _w);
                }
                else if(tmp == _CHANGE_GRAPHICS)
                {
                    if(lowGraphics)
                    {
                        renderer = std::make_unique<CPixel>(_w);
                        lowGraphics = false;
                    }
                    else
                    {
                        renderer = std::make_unique<CAscii>(_w);
                        lowGraphics = true;
                    }
                }
                else if(tmp == _EXIT) running = false;
            }
        }
        else
        {
            char _in = getInput(_w);

            if(_in == _ESC)
            {
                inMenu = true; // 27 == ESC
            }

            int _t = currMap->update(_in);

            if(_t == 1) inMenu = true;
            else if(_t > 1)
            {
                writeToFile(_t);
                gameMenu.endGame(_w, _t);
                inMenu = 1;
            }
            
            //render(_w);
            renderer.get()->render(currMap->worldMap);
        }

        t += std::chrono::milliseconds(50);
        std::this_thread::sleep_until(t);
    }
    if(currMap != nullptr) delete currMap;
}

void CGameLoop::writeToFile(int _t)
{
    if(_t > currMap->highScore) currMap->highScore = _t;

    std::vector<std::string> map;
    std::string line;
    std::ifstream inFileStream;
    std::ofstream outFileStream;
    std::stringstream _ss;

    inFileStream.open(fileName);

    while(getline(inFileStream, line))
        map.push_back(line);

    _ss << (currMap->highScore - (currMap->highScore % 100));
    _ss >> line;
    map.back() = line;

    outFileStream.open(fileName);

    for(auto i = map.begin(); i != map.end(); i++)
    {
        outFileStream << *i;
        if(*i != map.back()) outFileStream << std::endl;
    }
}
