#ifndef STAFF_H
#define STAFF_H

#include <vector>
#include <iostream>

#include "headers/weapon/weapon.h"
#include "headers/coutTag.h"
#include "headers/spell.h"

using namespace std;


class Staff : public Weapon
{
private:
    int m_damage;
    int m_manaIncrement;
    vector<Spell*> m_spells;
    int m_damageUpgrade;
    int m_manaIncrementUpgrade;
    int m_maxUpgrade;


public:

    Staff(string name, int handNumber, int damage, int manaIncrement, int maxUpgrade):
        Weapon(name, handNumber), m_damage(damage),
        m_manaIncrement(manaIncrement), m_damageUpgrade(0),
        m_manaIncrementUpgrade(0), m_maxUpgrade(maxUpgrade) {}

    int getDamage() const {return m_damage;};
    void incrementDamage(int dmg) {m_damage += dmg;};

    int getManaIncrement() const {return m_manaIncrement;};

    vector<Spell*> getSpells() const {return m_spells;};

    void showSpells(bool withBackOption=true) const;
    bool addSpell(Spell *sp);

    int getDamageUpgrade() const {return m_damageUpgrade;};
    void upgradeDamage(int upgrade);

    int getManaIncrementUpgrade() const {return m_manaIncrementUpgrade;};
    void upgradeManaIncrement(int upgrade);

    int getMaxUpgrade() const {return m_maxUpgrade;};

    void showStats(bool isHeroOwner = true) const;
    void clearSpells() {
        m_spells.clear();
        return;
    }

    ~Staff();
};

#endif // STAFF_H
