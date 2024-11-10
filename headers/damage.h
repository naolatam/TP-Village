#ifndef DAMAGE_H
#define DAMAGE_H

#include <string>
#include <cmath>

#include "headers/Element.h"
#include "headers/spell.h"

class Spell;

class Damage {
private:
    Element m_element;
    int m_amount;
    int m_level;
    Element m_weaknessElem;
    int m_weaknessPercent;
    Element m_resistanceElem;
    int m_resistancePercent;
    Spell *m_spell;
    int m_avoidChance;

public:
    // Constructeur
    Damage();
    Damage(int amount);
    Damage(const Element elem, int amount, int level,
           int weaknessPercent,
           int resistancePercent)
        : m_amount(amount), m_level(level),
        m_weaknessPercent(weaknessPercent),
        m_resistancePercent(resistancePercent), m_avoidChance(0)
    {setElement(elem);};


    Element getElement() const {return m_element;}
    void setElement(Element elem);

    int getAmount() const {return m_amount;}
    void setAmount(int amount) {m_amount = amount;};

    int getLevel() const {return m_level;}
    void setLevel(int lvl) {m_level = lvl;};

    Element getWeaknessElement() const {return m_weaknessElem;}

    int getWeagnessPercent() const {return m_weaknessPercent;}

    Element getResistanceElement() const {return m_resistanceElem;}

    int getResistancePercent() const {return m_resistancePercent;}

    Spell* getSpell() const {return m_spell;}
    void setSpell(Spell *spell) {delete m_spell; m_spell = spell;}

    int getAvoidChance() const {return m_avoidChance;};
    void setAvoidChance(int avoidChance) {m_avoidChance = avoidChance;};

    int getDamageOnElement(Element elem) const;
};


#endif // DAMAGE_H
