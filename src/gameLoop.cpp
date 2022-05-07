#include "gameLoop.hpp"

void CGameLoop::start()
{
    move(20, 20);
    printw("BOMBERMAN\n\tpress any button to start\n");
    running = 1;
    inMenu = 1;
    getch();
}

void CGameLoop::mainThread()
{
    while(running)
    {
/*
        //getInput();

        if(inMenu) gameMenu.update();
        else currMap.update();
*/
        if(inMenu) gameMenu.render(running, inMenu);
        else render();
    }

    //delete gameMenu;
}

void CGameLoop::render()
{
    clear();
    move(5, 5);
    printw
    ("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n■ 🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱⛩🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱■\n■ 🧱      👩‍🦯          📦    📦🤱📦          📦   📦         🧱■\n             ■ 🧱  🧱📦🧱  🧱  🧱📦🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱   🧱■\n■ 🧱📦                          📦    📦   📦               🧱■\n     ■ 🧱🧱  🧱  🧱📦🧱  🧱📦🧱  🧱  🧱  🧱  🧱  🧱  🧱🥵🧱  🧱 🧱■\n■ 🧱  📦              📦📦      📦         📦               🧱■\n         ■ 🧱  🧱  🧱📦🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱   🧱■\n■ 🧱    📦          📦          📦       📦        📦       🧱■\n■ 🧱🧱  🧱🧟‍♂️🧱  🧱  🧱🥵🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱 🧱■\n■ 🧱        📦            📦    📦      📦         📦       🧱■\n■ 🧱  🧱  🧱  🧱📦🧱  🧱  🧱📦🧱  🧱  🧱  🧱  🧱  🧱  🧱   🧱■\n■ 🧱    📦          📦🧟‍♂️📦        📦        📦       📦     🧱■\n                                                           ■ 🧱🧱  🧱📦🧱  🧱  🧱  🧱📦🧱📦🧱  🧱  🧱  🧱  🧱  🧱  🧱 🧱■\n■ 🧱  📦      📦                                 🦄         🧱■\n■ 🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🚪🧱🧱🧱🧱🧱■\n■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    getch();
}