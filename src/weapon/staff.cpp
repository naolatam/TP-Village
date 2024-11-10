#include "../../headers/weapon/staff.h"

void Staff::showSpells(bool withBackOption) const {

    cout << INFO_TAG_START << endl;
    if(withBackOption == true) {
        cout << "[0] Retour" << endl;
    }
    for (size_t i = 0; i < m_spells.size(); i++) {
        cout << "[" << i +1 << "] "
             << "Nom: "<< m_spells[i]->getName() << " | "
             << "Element: " << getElementString(m_spells[i]->getElement())
             << " | " << "B. dmg: " << m_spells[i]->getDamage() << endl;
    }
    cout << INFO_TAG_END << endl;
}

bool Staff::addSpell(Spell *sp) {
    bool alreadyIn = false;
    for (size_t i =0; i < m_spells.size();i ++) {
        if (sp->equalsTo(m_spells[i]) == true) {
            alreadyIn = true;
            break;
        }
    }
    if (alreadyIn == true) {
        return false;
    }

    m_spells.push_back(sp);
    return true;
}



void Staff::showStats(bool isHeroOwner) const {
    cout << INFO_TAG_START << endl;
    if (isHeroOwner) {
        cout << "Mon sceptre se prénomme " << m_name << endl;
    }else {
        cout << "Le sceptre se prénomme " << m_name << endl;
    }
    cout << "Il s'utilise a " << m_takingHandNumber
         << " main(s)!" << endl
         << "Il permet d'utiliser " << m_spells.size()
         << " sorts!" << endl
         << "Il fait "<<  getDamage() << " dégats" <<endl
         << "Et contient " << m_manaIncrement << " de mana" << endl
         << INFO_TAG_END << endl;
    return;
}


void Staff::upgradeDamage(int upgrade) {
    if(m_damageUpgrade < m_maxUpgrade) {
        m_damageUpgrade +=1;
        m_damage += upgrade;
    }
    return;
}

void Staff::upgradeManaIncrement(int upgrade) {
    if(m_manaIncrementUpgrade < m_maxUpgrade) {
        m_manaIncrementUpgrade +=1;
        m_manaIncrement += upgrade;
    }
    return;
}

Staff::~Staff() {
    for(Spell* s:m_spells){
        delete s;
    }
}



