#ifndef PALADIN_H
#define PALADIN_H

#include <thread>

#include "headers/entity/hero/hero.h"
#include "headers/weapon/shield.h"
#include "headers/weapon/sword.h"

class Paladin : public Hero
{
private:
    Shield *m_shield;
    Sword *m_sword;

    void createBasicSwordAndShield();
public:
    Paladin(std::string name, int freeHands, int maxHp, int hp,
            int gold,int baseDamage,
            int baseDefence, int criticalChance, int criticalDamage,
            int baseAgility) : Hero(name, freeHands, maxHp, hp, gold,
               baseDamage, baseDefence, baseAgility, criticalChance,
               criticalDamage) {createBasicSwordAndShield();};

    void introduce() const;
    void insult(Entity* entity) const;
    void removeEquipementBonus();
    void addEquipementBonus();

    int attack(Entity* entity);
    int takeDamage(Damage* dmg);
    int getDamage() const;
    Damage* getAttackDamage() ;

    Shield* getShield() const {return m_shield;};
    void setShield(Shield* shield, bool deleteActual=true);

    Sword* getSword() const {return m_sword;};
    void setSword(Sword* sword, bool deleteActual=true);


    ~Paladin();

};

#endif // PALADIN_H
