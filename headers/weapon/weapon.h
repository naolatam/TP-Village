#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include "headers/coutTag.h"

using namespace std;

class Weapon
{
protected:
    string m_name;
    int m_takingHandNumber;

public:

    Weapon(string name, int handNumber)
        : m_name(name), m_takingHandNumber(handNumber) {};

    string getName() {return m_name;}
    int getTakingHandNumber() {return m_takingHandNumber;}

    virtual void showStats(bool isHeroOwner=true) const;
    virtual ~Weapon() {};
};

#endif // WEAPON_H
