#include "../../headers/potion/potion.h"

void Potion::risePrice(int percent) {
    if (percent <= 0) return;
    m_price *= percent/100;
    return;
}



bool Potion::equalsTo(const Potion *p) const {
    if (p == nullptr) {
        return false;
    }
    return m_name == p->m_name &&
           m_type == p->m_type &&
           m_duration == p->m_duration &&
           m_manaRegen == p->m_manaRegen &&
           m_strengthIncrease == p->m_strengthIncrease &&
           m_damage == p->m_damage &&
           m_defense == p->m_defense &&
           m_healRegen == p->m_healRegen &&
           m_agilityIncrease == p->m_agilityIncrease &&
           m_throwable == p->m_throwable &&
           m_price == p->m_price;
}

int Potion::throwOn(Entity *e) const {
    if (m_throwable == false) {return -2;}

    if (!e->isAlive()) {return -1;}

    Damage *dmg = new Damage();
    dmg->setElement(m_elem);
    dmg->setAvoidChance(20);
    dmg->setLevel(m_level);
    dmg->setAmount(m_damage);

    int damageTaken = e->takeDamage(dmg);
    delete dmg;
    return damageTaken;


}


void Potion::displayProperties() const {
    string properties = "";
    if (m_name != "") properties +=
        "Name: " + m_name + " | ";
    if (!m_type.empty()) properties += "Type: " + m_type + " | ";
    if (m_elem != Element::DEFAULT) properties += "Element: " + getElementString(m_elem) + " | ";
    if (m_level != 0) properties += "Level: " + to_string(m_level) + " | ";
    if (m_duration != 0) properties += "Duration: " + to_string(m_duration) + " | ";
    if (m_manaRegen != 0) properties += "Mana Regen: " + to_string(m_manaRegen) + " | ";
    if (m_strengthIncrease != 0) properties += "Strength Increase: " + to_string(m_strengthIncrease) + " | ";
    if (m_damage != 0) properties += "Damage: " + to_string(m_damage) + " | ";
    if (m_defense != 0) properties += "Defense: " + to_string(m_defense) + " | ";
    if (m_healRegen != 0) properties += "Heal Regen: " + to_string(m_healRegen) + " | ";
    if (m_agilityIncrease != 0) properties += "Agility Increase: " + to_string(m_agilityIncrease) + " | ";
    if (m_throwable) properties += "Throwable: Yes | ";
    if (m_price != 0) properties += "Price: " + to_string(m_price) + " | ";
    if(properties != "") {
        properties.resize(properties.size() - 3);
    }
    cout << properties << endl;

}
