#include "headers/main.h"

int main()
{
    system("chcp 65001 & cls");
    Game* g = GameLoader::loadGame();
    if(g == nullptr) g = GameLoader::createNewGame();
    g->Play();
}
