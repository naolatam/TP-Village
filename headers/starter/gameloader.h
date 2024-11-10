G#ifndef GAMELOADER_H
#define GAMELOADER_H


#include "headers/game.h"
#include "headers/starter/herocreator.h"


class GameLoader
{
public:
    GameLoader() {};
    static Game* loadGame();
    static Game* createNewGame();

    ~GameLoader() {};
};

#endif // GAMELOADER_H
