#ifndef SWORD_H
#define SWORD_H

#include "weapon.h"

class Sword : public Weapon
{
private:
    int m_damage;
    int m_agilityIncrease;
    int m_weigth;
    int m_damageUpgrade;
    int m_agilityIncreaseUpgrade;
    int m_weigthUpgrade;
    int m_maxUpgrade;

public:
    Sword(string name, int handNumber, int damage,
          int agilityIncrease, int weigth, int maxUpgrade):
        Weapon(name, handNumber), m_damage(damage),
        m_agilityIncrease(agilityIncrease), m_weigth(weigth),
        m_damageUpgrade(0), m_agilityIncreaseUpgrade(0),
        m_weigthUpgrade(0), m_maxUpgrade(maxUpgrade) {}


    int getDamage() const {return m_damage;};
    void increaseDamage(int dmgIncr) {m_damage += dmgIncr;};

    int getAgilityIncrease() const {return m_agilityIncrease;};
    void increaseAgility(int agiIncr) {m_agilityIncrease += agiIncr;};

    int getWeigth() const {return m_weigth;};

    int getDamageUpgrade() const {return m_damageUpgrade;};
    void upgradeDamage(int upgrade);

    int getAgilityIncreaseUpgrade() const {return m_agilityIncreaseUpgrade;};
    void upgradeAgilityIncrease(int upgrade);


    int getWeigthUpgrade() const {return m_weigthUpgrade;};
    void upgradeWeigth(int upgrade);



    int getMaxUpgrade() const {return m_maxUpgrade;};



    void showStats(bool isHeroOwner= true) const;

    ~Sword() {};

};

#endif // SWORD_H
