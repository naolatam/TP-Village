#ifndef ENTITY_H
#define ENTITY_H

class Potion;
class Inventory;

#include <string>

#include "headers/potion/potion.h"
#include "headers/inventory/inventory.h"
#include "headers/damage.h"
#include "headers/coutTag.h"
#include "headers/damage.h"

using namespace std;

class Entity {
protected:
    // Attributes
    string m_name;       // Nom de l'entité
    int m_maxHp;              // Points de vie max
    int m_hp;                 // Points de vie actuels
    int m_gold;               // Or
    int m_baseDamage;         // Dégâts de base
    int m_baseDefense;        // Défense de base
    int m_criticalChance;
    int m_criticalDamage;
    int m_baseAgility;
    int m_level;
    int m_xp;
    Inventory* m_inventory;


public:
    // Constructor
    Entity(std::string name, int maxHp, int hp, int gold, int baseDamage, int baseDefence,
           int criticalChance, int criticalDamage, int baseAgility);

    std::string getName() const { return m_name; }

    int getMaxHp() const { return m_maxHp; }
    void setMaxHp(int maxHp) { m_maxHp = maxHp; }

    int getHp() const { return m_hp; }
    void setHp(int hp) { m_hp = hp; }

    int getGold() const { return m_gold; }
    void setGold(int gold) { m_gold = gold; }

    int getBaseDamage() const { return m_baseDamage; }
    void setBaseDamage(int baseDamage) { m_baseDamage = baseDamage; }

    int getBaseDefence() const { return m_baseDefense; }
    void setBaseDefence(int baseDefence) { m_baseDefense = baseDefence; }

    int getBaseAgility() const { return m_baseAgility; }
    void setBaseAgility(int baseAgility) { m_baseAgility = baseAgility; }

    int getCriticalChance() const { return m_criticalChance; }
    void setCriticalChance(int criticalChance) { m_criticalChance = criticalChance; }

    int getCriticalDamage() const { return m_criticalDamage; }
    void setCriticalDamage(int criticalDamage) { m_criticalDamage = criticalDamage; }

    Inventory* getInventory() const { return m_inventory; }
    void setInventory(Inventory* inventory) { m_inventory = inventory; }

    int getLevel() const {return m_level;}
    virtual void levelUp();

    int getXp() const {return m_xp;}
    void addXp(int amount) {m_xp += amount;}

    bool isCritical() const;
    void addHp(int hp);
    bool isAlive() const;

    virtual int attack(Entity *entity);
    virtual void introduce() const;
    virtual int takeDamage(Damage *dmg);
    virtual void insult(Entity *entity) const;
    virtual int getDamage() const;
    virtual int getDefense() const;
    virtual bool avoidAttack(Damage *dmg) const;

    virtual ~Entity();


};


#endif
