#ifndef WARRIOR_H
#define WARRIOR_H

class Sword;

#include <thread>

#include "headers/entity/hero/hero.h"
#include "headers/weapon/sword.h"

class Warrior : public Hero
{

private:
    Sword *m_sword;

    void createBasicSword();
public:
    Warrior(std::string name, int freeHands, int maxHp, int hp,
            int gold,int baseDamage,
            int baseDefence, int criticalChance, int criticalDamage,
            int baseAgility) : Hero(name, freeHands, maxHp, hp, gold,
               baseDamage, baseDefence, baseAgility, criticalChance,
               criticalDamage) {createBasicSword();};

    Sword* getSword() const {return m_sword;};
    void setSword(Sword* sword, bool deleteActual=true);


    void introduce() const;
    void insult(Entity* entity) const;
    void removeEquipementBonus();
    void addEquipementBonus();

    int attack(Entity* entity);
    int takeDamage(Damage* dmg);
    Damage* getAttackDamage() ;


    int getDamage() const;

    ~Warrior();
};

#endif // WARRIOR_H
