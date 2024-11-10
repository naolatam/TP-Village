#ifndef SPELL_H
#define SPELL_H

#include <iostream>

#include "headers/Element.h"

using namespace std;

class Spell
{
private:
    string m_name;
    Element m_element;
    int m_minLevel;
    int m_damage;
    int m_manaConsumption;
    int m_avoidChance;
public:
    Spell(string name, Element elem, int minLevel, int damage,
          int manaConsumption, int avoidChance)
        : m_name(name), m_element(elem), m_minLevel(minLevel),
        m_damage(damage), m_manaConsumption(manaConsumption),
        m_avoidChance(avoidChance) {};

    string getName() const {return m_name;};
    Element getElement() const {return m_element;};
    int getMinLevel() const {return m_minLevel;};
    int getDamage() const {return m_damage;};
    int getManaConsumption() const {return m_manaConsumption;};
    int getAvoidChance() const {return m_avoidChance;};

    bool equalsTo(Spell *sp);
};

#endif // SPELL_H
