#include <ncurses.h>

class CGameLoop
{
    bool running;
    bool inMenu;

    public:
        void start();

        void mainThread();
};
