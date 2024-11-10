#ifndef HEROCREATOR_H
#define HEROCREATOR_H

#include <iostream>
#include <thread>


#include "headers/dataManager/spelldatamanager.h"
#include "headers/dataManager/potiondatamanager.h"
#include "headers/entity/hero/mage.h"
#include "headers/entity/hero/paladin.h"
#include "headers/entity/hero/warrior.h"
#include "headers/potion/potion.h"
#include "headers/utils.h"

using namespace std;

class HeroCreator
{
private:
    static int askAInt(int min,int max);
    static int askHeroClass();
    static string askHeroName();
    static int askHeroMaxHp();
    static int askHeroGold();
    static int askHeroDamage();
    static int askHeroDefense();
    static int askHeroCriticalChance();
    static int askHeroCriticalDamage();
    static int askHeroAgility();
    static int askHeroManaMax();
    static int askHeroManaRegen();
    static Element askHeroElem();


    static Hero* m_hero;
public:
    HeroCreator() {};
    static Hero* getHero(SpellDataManager* spellDataManager);
    ~HeroCreator() {delete m_hero;};
};

#endif // HEROCREATOR_H
