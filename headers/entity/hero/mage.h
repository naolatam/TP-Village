#ifndef MAGE_H
#define MAGE_H

#include <iostream>
#include <chrono>
#include <thread>

#include "headers/entity/hero/hero.h"
#include "headers/coutTag.h"
#include "headers/Element.h"
#include "headers/weapon/staff.h"
#include "headers/spell.h"


class Mage : public Hero
{
private:
    int m_mana;
    int m_manaMax;
    int m_manaRegen;
    Staff* m_staff;
    Element m_element;

    void createAndAssignDefaultStaff();

public:
    // Constructor
    Mage(std::string name, int freeHands, int maxHp, int hp, int gold,int baseDamage,
         int baseDefence, int criticalChance, int criticalDamage, int baseAgility, int manaMax, int manaRegen, Element elem)
        : Hero(name, freeHands, maxHp, hp, gold, baseDamage, baseDefence, baseAgility, criticalChance, criticalDamage),
        m_mana(manaMax), m_manaMax(manaMax), m_manaRegen(manaRegen), m_element(elem) {createAndAssignDefaultStaff();}

    Staff* getStaff() {return m_staff;}
    void setStaff(Staff* staff, bool deleteActual=true);

    int getMana() const {return m_mana;};
    void useMana(int consumption) {m_mana -= consumption;};

    int getDamage() const;

    int getMaxMana() const {return m_manaMax;};
    void setMaxMana(int manaMax) {m_manaMax = manaMax;};

    int getManaRegen() const {return m_manaRegen;};
    void setManaRegen(int manaRegen) {m_manaRegen = manaRegen;};

    Element getElement() const {return m_element;};
    void setElement(Element elem) {m_element = elem;};

    void regenMana();
    void regenMana(int manaRegen);

    void introduce() const;
    void insult(Entity* entity) const;
    void usePotion(Potion*p);
    void removeEquipementBonus();
    void addEquipementBonus();
    int attack(Entity* entity);
    int takeDamage(Damage* dmg);

    int askForASpell() const;
    bool checkIfSpellIsUsable(Spell* sp) const;
    Damage* getAttackDamage() ;

    ~Mage();

};

#endif // MAGE_H
