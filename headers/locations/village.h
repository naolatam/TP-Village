#ifndef VILLAGE_H
#define VILLAGE_H

class Game;

#include <vector>
#include <string>

#include "headers/locations/buildings/mine.h"
#include "headers/locations/buildings/hostel.h"
#include "headers/locations/buildings/shop.h"
#include "headers/locations/buildings/forge.h"



using namespace std;

class Village
{
private:
    Game& m_game;
    vector<Building*> m_buildings;
    int m_entranceFees;
    int m_id;
    string m_name;
    bool m_visited;


public:
    Village(Game& game, int id);

    void enter();
    void inside();

    string getName() const {return m_name;};
    int getId() const {return m_id;};
    int getEntranceFees() const {return m_entranceFees;};

    int getBuildingCountFromType(string type);
};

#endif // VILLAGE_H
