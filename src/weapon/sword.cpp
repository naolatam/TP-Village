#include "headers/weapon/sword.h"



void Sword::showStats(bool isHeroOwner) const {
    cout << INFO_TAG_START << endl;
    if(isHeroOwner) {
        cout << "Mon épée se prénomme " << m_name << endl;
    }else {
        cout << "L'épée se prénomme " << m_name << endl;
    }
    cout << "Elle se porte à " << m_takingHandNumber
         << " main(s)!" << endl
         << "Elle pèse " << m_weigth;
    if (m_agilityIncrease > 0) {
        cout << " et augmente mon agilité de " << m_agilityIncrease;
    }else if (m_agilityIncrease < 0) {
        cout << " et diminue mon agilité de " << m_agilityIncrease*-1;
    }
    cout << endl << "Elle fait aussi " << m_damage << " dégats!";
    cout << endl << INFO_TAG_END << endl;
    return;
}

void Sword::upgradeDamage(int upgrade) {
    if(m_damageUpgrade < m_maxUpgrade) {
        m_damageUpgrade +=1;
        m_damage += upgrade;
    }
    return;
}

void Sword::upgradeAgilityIncrease(int upgrade) {
    if(m_agilityIncreaseUpgrade < m_maxUpgrade) {
        m_agilityIncreaseUpgrade +=1;
        m_agilityIncrease += upgrade;
        if(m_agilityIncrease > 80) m_agilityIncrease = 80;
    }
    return;
}


void Sword::upgradeWeigth(int upgrade) {
    if(m_weigthUpgrade < m_maxUpgrade) {
        m_weigthUpgrade +=1;
        m_weigth -= upgrade;
    }
    if(m_weigth < 0) m_weigth = 0;
    return;
}
