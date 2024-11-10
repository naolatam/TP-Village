#include "headers/weapon/shield.h"



void Shield::showStats(bool isHeroOwner) const {
    cout << INFO_TAG_START << endl;
    if(isHeroOwner) {
        cout << "Mon bouclier se prénomme " << m_name << endl;
    }else {
        cout << "Le bouclier se prénomme " << m_name << endl;
    }
    cout << "Il pèse " << m_weigth
         << "kg! et a une défense de "
         << m_defense << endl
         << INFO_TAG_END << endl;
    return;
}

void Shield::upgradeDefense(int upgrade) {
    if(m_defenseUpgrade < m_maxUpgrade) {
        m_defenseUpgrade +=1;
        m_defense += upgrade;
    }
    return;
}


void Shield::upgradeWeigth(int upgrade) {
    if(m_weigthUpgrade < m_maxUpgrade) {
        m_weigthUpgrade +=1;
        if(m_weigth - upgrade < 0) {
            m_weigth = 0;
            return;
        }
        m_weigth -= upgrade;

    }
    return;
}

