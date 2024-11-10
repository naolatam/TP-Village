#ifndef LOCATION_H
#define LOCATION_H


#include <string>

#include "headers/game.h"

using namespace std;


class Building
{

protected:
    Game& m_game;
    string m_type;
public:
    Building(Game& game, string type): m_game(game), m_type(type) {};

    string getType() const {return m_type;};

    virtual void enter() = 0;
    virtual ~Building() {};

};

#endif // LOCATION_H
