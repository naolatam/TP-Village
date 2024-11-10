#ifndef POTION_H
#define POTION_H

class Entity;

#include <string>
#include "headers/Element.h"
#include "headers/entity/entity.h"


using namespace std;

class Potion {
private:
    string m_name;
    string m_type;
    Element m_elem;
    int m_level;
    int m_duration;
    int m_manaRegen;
    int m_strengthIncrease;
    int m_damage;
    int m_defense;
    int m_healRegen;
    int m_agilityIncrease;
    bool m_throwable;
    int m_price;

public:
    // Constructeur
    Potion(const string& name, const string& type, Element elem, int level, int duration, int manaRegen,
           int strengthIncrease, int damage, int defense, int healRegen,
           int agilityIncrease, bool throwable, int price)
        : m_name(name), m_type(type), m_elem(elem), m_level(level), m_duration(duration), m_manaRegen(manaRegen),
        m_strengthIncrease(strengthIncrease), m_damage(damage), m_defense(defense),
        m_healRegen(healRegen), m_agilityIncrease(agilityIncrease),
        m_throwable(throwable), m_price(price) {}

    // Destructeur virtuel

    // Getters et setters
    const string& getName() const { return m_name; }
    void setName(const string& name) { m_name = name; }

    const string& getType() const { return m_type; }

    Element getElement() const {return m_elem;};

    int getLevel() const {return m_level;};

    int getDuration() const { return m_duration; }
    void useOneTime() {m_duration -=1;};

    int getManaRegen() const { return m_manaRegen; }

    int getStrengthIncrease() const { return m_strengthIncrease; }

    int getDamage() const { return m_damage; }

    int getDefense() const { return m_defense; }

    int getHealRegen() const { return m_healRegen; }

    int getAgilityIncrease() const { return m_agilityIncrease; }

    bool isThrowable() const { return m_throwable; }

    int getPrice() const { return m_price; }

    void risePrice(int percent);
    int throwOn(Entity *e) const;
    bool equalsTo(const Potion *p) const;

    void displayProperties() const;

    virtual ~Potion() {}



};


#endif // POTION_H
