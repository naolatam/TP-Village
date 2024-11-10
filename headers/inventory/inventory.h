#ifndef INVENTORY_H
#define INVENTORY_H

class Potion;

#include <vector>

#include "headers/potion/potion.h"

using namespace std;

class Inventory
{

private:
    int m_size;
    vector<Potion*> m_potions;

public:
    Inventory(int maxSize) : m_size(maxSize) {};

    int getSize() const {return m_size;};
    void setSize(int maxSize);

    int getUsedSize() const {return m_potions.size();};

    Potion* getPotion(int idx) const {return m_potions[idx];};
    vector<Potion*> getPotions() const {return m_potions;};

    void addPotion(Potion *p);
    void removePotion(Potion *p);
    void showPotions(bool withReturn = false) const;
    void clear();
    bool haveThrowablePotion();
    bool haveConsumablePotion();


    ~Inventory();

};

#endif // INVENTORY_H
