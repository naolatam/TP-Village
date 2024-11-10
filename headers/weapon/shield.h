#ifndef SHIELD_H
#define SHIELD_H

#include "weapon.h"

class Shield : public Weapon
{
private:
    int m_defense;
    int m_weigth;
    int m_defenseUpgrade;
    int m_weigthUpgrade;
    int m_maxUpgrade;
public:

    Shield(string name, int handNumber, int defense, int m_weigth,
           int maxUpgrade):
        Weapon(name, handNumber), m_defense(defense), m_weigth(m_weigth),
        m_defenseUpgrade(0), m_weigthUpgrade(0), m_maxUpgrade(maxUpgrade)
        {}

    int getDefense() const {return m_defense;};
    void increaseDefense(int dfsIncr) {m_defense += dfsIncr;};

    int getWeigth() const {return m_weigth;};

    int getDefenseUpgrade() const {return m_defenseUpgrade;};
    void upgradeDefense(int upgrade);

    int getWeigthUpgrade() const {return m_weigthUpgrade;};
    void upgradeWeigth(int upgrade);

    int getMaxUpgrade() const {return m_maxUpgrade;};

    void showStats(bool isHeroOwner = true) const;

    ~Shield() {};
};

#endif // SHIELD_H
