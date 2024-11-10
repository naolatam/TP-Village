#ifndef MINE_H
#define MINE_H


#include <random>
#include <string>
#include <thread>

#include "headers/locations/buildings/building.h"
#include "headers/entity/monster.h"
#include "headers/weapon/sword.h"
#include "headers/entity/hero/hero.h"
#include "headers/weapon/shield.h"
#include "headers/coutTag.h"


class Mine : public Building
{
private:
    int m_level, m_difficulty;
    int m_monsterCount;
    Monster* m_actualMonster;
    int fib(int number);

    Monster* generateMonster();
    void heroTurn();
    void monsterTurn();
    void showHps() const;
public:
    Mine(Game& game);

    int getLevel() const {return m_level;};
    int getDifficulty() const {return m_difficulty;};

    void enter();
    void inside();

    ~Mine() { delete m_actualMonster;};
};

#endif // MINE_H
