#include "../../headers/inventory/inventory.h"
#include <algorithm>
#include <thread>

void Inventory::setSize(int maxSize) {
    if (maxSize < 1) return;
    m_size = maxSize;
    return;
}

void Inventory::showPotions(bool withReturn) const {
    cout << INFO_TAG_START << endl;
    if(withReturn) cout << "[0] Retour" << endl;
    for (size_t i = 0; i < m_potions.size(); i++) {
        cout << "[" << i +1 << "] ";
        m_potions[i]->displayProperties();
    }
}

void Inventory::addPotion(Potion *p) {
    if(m_potions.size() == m_size) {
        cout << ERROR_TAG_START << endl;
        cout << "Tu n'as plus de place dans ton inventaire!" << endl;
        cout << ERROR_TAG_END << endl;
        return;
    };
    m_potions.push_back(p);
    return;
}

void Inventory::removePotion(Potion *p) {
    for(size_t i = 0; i < m_potions.size(); i++) {
        if(p == m_potions[i]) {
            m_potions.erase(m_potions.begin() + i);
            return;
        }
    }
    return;
}

void Inventory::clear() {
    for(size_t i = m_potions.size() -1; i >=0; i--) {
        delete m_potions[i];
    }
    m_potions.clear();
}

bool Inventory::haveThrowablePotion() {
    for(Potion* p:m_potions) {
        if(p->isThrowable() == true) return true;
    }
    return false;
}

bool Inventory::haveConsumablePotion() {
    for(Potion* p:m_potions) {
        if(p->isThrowable() == false) return true;
    }
    return false;
}

Inventory::~Inventory() {
    for(Potion* p:m_potions) {
        delete p;
    }
}
