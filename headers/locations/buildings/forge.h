#ifndef FORGE_H
#define FORGE_H

#include <thread>

#include "headers/locations/buildings/building.h"

#include "headers/entity/hero/mage.h"
#include "headers/entity/hero/paladin.h"
#include "headers/entity/hero/warrior.h"


class Forge : public Building
{
private:
    int m_priceCoef;
    int m_luckBonus;
public:
    Forge(Game& game);

    void enter();

    void insideForMage();
    void upgradeStaff(Mage* m);
    void newSpellForStaff(Mage* m);

    void insideForPaladin();
    void upgradeShield(Paladin* p);
    void upgradeSword(Paladin* p);

    void insideForWarrior();
    void extracted(Warrior *&w, int &damageUpgradePrice);
    void upgradeSword(Warrior *w);

    ~Forge() {};
};

#endif // FORGE_H
