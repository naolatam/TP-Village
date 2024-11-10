#ifndef MERCHANT_H
#define MERCHANT_H


#include <thread>

#include "headers/entity/entity.h"
#include "headers/entity/hero/hero.h"
#include "headers/pattern/merchantSellEmitter.h"
#include "headers/utils.h"

class Merchant : public Entity, public MerchantSellEmitter
{
private:
public:
    Merchant(std::string name, int maxHp, int hp, int gold, int baseDamage, int baseDefence,
            int criticalChance, int criticalDamage, int baseAgility)
        : Entity(name, maxHp, hp, gold, baseDamage, baseDefence,
                 criticalChance, criticalDamage, baseAgility) {};

    void risePrice(int percent) const;
    int buy(Hero *h);
    bool checkIfPotionIndexIsValid(int ptIdx, Hero *h) const;

    int attack(Entity *entity);
    void introduce() const;
    int takeDamage(Damage *dmg);
    void insult(Entity *entity) const;
    int getDamage() const;
    int getDefense() const;

    Damage* getAttackDamage() const;

    ~Merchant() {};

};


#endif // MERCHANT_H
