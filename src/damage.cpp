#include "../headers/damage.h"

Damage::Damage() {
    m_element = Element::DEFAULT;
    m_weaknessElem = Element::VOID;
    m_resistanceElem = Element::VOID;
    m_weaknessPercent = 100;
    m_resistancePercent = 100;
    m_amount= 0;
    m_level = 0;
    m_avoidChance = 0;
}

Damage::Damage(int amount) {
    m_element = Element::DEFAULT;
    m_weaknessElem = Element::VOID;
    m_resistanceElem = Element::VOID;
    m_weaknessPercent = 100;
    m_resistancePercent = 100;
    m_amount= amount;
    m_level = 0;
    m_avoidChance = 0;
}

void Damage::setElement(Element elem) {
    m_weaknessElem = static_cast<Element>(static_cast<int>(ElementWeakness(static_cast<int>(elem))));
    m_resistanceElem = static_cast<Element>(static_cast<int>(ElementResistance(static_cast<int>(elem))));
    m_element = elem;
    return;
}

int Damage::getDamageOnElement(Element elem) const {
    int amount = m_amount;
    if (elem == m_weaknessElem) amount *= m_weaknessPercent;
    else if (elem == m_resistanceElem) amount *= m_resistancePercent;
    amount += floor((1/3)*m_level);
    return amount;
}
