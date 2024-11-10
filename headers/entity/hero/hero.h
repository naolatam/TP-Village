#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>

#include "headers/entity/entity.h"

using namespace std;


class Hero : public Entity {
protected:
    int m_freeHandsNb;                                // Nombre de mains libres
    vector<Potion*> m_temporaryStregthItem;        // Potions qui affectent temporairement les dégâts
    vector<Potion*> m_temporaryDefenseItem;       // Potions qui affectent temporairement la défense
    vector<Potion*> m_temporaryAgilityItem;
    bool m_isEquipementBonusActived;


public:
    // Constructor
    Hero(std::string name, int freeHands, int maxHp, int hp, int gold,
        int baseDamage, int baseDefence, int criticalChance, int criticalDamage, int baseAgility)
        : Entity(name, maxHp, hp, gold, baseDamage, baseDefence, baseAgility, criticalChance, criticalDamage),
        m_freeHandsNb(freeHands) {}

    int getFreeHandsNb() const { return m_freeHandsNb; }
    void setFreeHandsNb(int freeHands) { m_freeHandsNb = freeHands; }

    std::vector<Potion*> getTemporaryStregthItem() const { return m_temporaryStregthItem; }
    void addTemporaryStrengthItem(Potion* potion);

    std::vector<Potion*> getTemporaryDefenseItem() const { return m_temporaryDefenseItem; }
    void addTemporaryDefenseItem(Potion* potion);

    std::vector<Potion*> getTemporaryAgilityItem() const { return m_temporaryAgilityItem; }
    void addTemporaryAgilityItem(Potion* potion);

    void useTemporaryEffect();
    Potion* askForAPotion(bool throwable) const;

    virtual int getDamage() const;
    virtual Damage* getAttackDamage();
    virtual int getDefense() const;
    virtual void throwPotion(Potion *p, Entity *e);
    virtual void usePotion(Potion*p);
    virtual void removeEquipementBonus();
    virtual void addEquipementBonus();

    virtual bool avoidAttack(Damage* dmg) const;

    ~Hero();
};

#endif // HERO_H
