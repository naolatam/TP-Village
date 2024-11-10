#include "headers/weapon/weapon.h"

void Weapon::showStats(bool isHeroOwner) const {
    cout << INFO_TAG_START << endl;
    if(isHeroOwner) {
        cout << "Mon arme se prénomme " << m_name << endl;
    }else {
        cout << "L'arme se prénomme " << m_name << endl;

    }

    cout << "C'est une arme à " << m_takingHandNumber
    << " mains!" << endl
    << INFO_TAG_END << endl;
    return;
}
