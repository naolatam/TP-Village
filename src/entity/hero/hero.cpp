#include "headers/entity/hero/hero.h"

void Hero::addTemporaryAgilityItem(Potion *potion) {
    if(potion->getAgilityIncrease() == 0) return delete potion;
    m_temporaryAgilityItem.push_back(potion);
}

void Hero::addTemporaryDefenseItem(Potion *potion) {
    if(potion->getDefense() == 0) return delete potion;
    m_temporaryDefenseItem.push_back(potion);
}

void Hero::addTemporaryStrengthItem(Potion *potion) {
    if(potion->getStrengthIncrease() == 0) return delete potion;
    m_temporaryStregthItem.push_back(potion);
}

void Hero::useTemporaryEffect() {
    for (size_t i =0; i < m_temporaryStregthItem.size(); i++){
        m_temporaryStregthItem[i]->useOneTime();
        if(m_temporaryStregthItem[i]->getDuration() == 0) delete m_temporaryStregthItem[i];
    }
    for (size_t i =0; i < m_temporaryAgilityItem.size(); i++){
        m_temporaryAgilityItem[i]->useOneTime();
        if(m_temporaryAgilityItem[i]->getDuration() == 0) delete m_temporaryAgilityItem[i];
    }
    for (size_t i =0; i < m_temporaryDefenseItem.size(); i++){
        m_temporaryDefenseItem[i]->useOneTime();
        if(m_temporaryDefenseItem[i]->getDuration() == 0) delete m_temporaryDefenseItem[i];
    }
    for (size_t i =m_temporaryStregthItem.size(); i>0; i--) {
        if(m_temporaryStregthItem[i] == nullptr) m_temporaryStregthItem.erase( m_temporaryStregthItem.begin() + i);
    }
    for (size_t i =m_temporaryAgilityItem.size(); i>0; i--) {
        if(m_temporaryAgilityItem[i] == nullptr) m_temporaryAgilityItem.erase( m_temporaryAgilityItem.begin() + i);
    }
    for (size_t i = m_temporaryDefenseItem.size(); i>0; i--) {
        if(m_temporaryDefenseItem[i] == nullptr) m_temporaryDefenseItem.erase( m_temporaryDefenseItem.begin() + i);
    }
}


int Hero::getDamage() const {
    int amount = 0;

    amount += m_baseDamage;
    for (size_t i =0; i < m_temporaryStregthItem.size(); i++)
    {
        amount += m_temporaryStregthItem[i]->getStrengthIncrease();
    }

    amount += floor((1/3)*m_level);

    return amount;
}

Damage* Hero::getAttackDamage() {
    int amount = 0;

    amount += m_baseDamage;
    for (size_t i =0; i < m_temporaryStregthItem.size(); i++)
    {
        amount += m_temporaryStregthItem[i]->getStrengthIncrease();
    }

    amount += floor((1/3)*m_level);

    return new Damage(amount);
}

void Hero::removeEquipementBonus() {
    m_isEquipementBonusActived = false;
    return;
}

void Hero::addEquipementBonus() {
    m_isEquipementBonusActived = true;
    return;
}

Potion* Hero::askForAPotion(bool throwable) const {
    if(throwable){
        if(!m_inventory->haveThrowablePotion()) {
            cout << ERROR_TAG_START
                 << "Tu n'as aucune potion jetable!"
                 << ERROR_TAG_END << endl;
            return nullptr;
        }
    }else {
        if(!m_inventory->haveConsumablePotion()) {
            cout << ERROR_TAG_START
                 << "Tu n'as aucune potion consommable!"
                 << ERROR_TAG_END << endl;
            return nullptr;
        }
    }


    vector<Potion*> p;
    cout << "[0] Retour" << endl;
    for(size_t i = 0; i < m_inventory->getUsedSize(); i++) {
        if(m_inventory->getPotion(i)->isThrowable() == throwable) { // check if potion is not throwable
            p.push_back(m_inventory->getPotion(i)); // add potion to the temporary vector
            cout << "[" << p.size() << "] ";
            m_inventory->getPotion(i)->displayProperties();
        }
    }
    bool isValid = false;
    int pIdx;
    do {
        cout << "Quel potion voulez vous utiliser? ";
        cin >> pIdx;
        if(pIdx < 0 || pIdx > p.size() || cin.fail()) {
            cout << ERROR_TAG_START << "Index invalide!"
                 << "Merci de choisir un nombre entre 0 et " << p.size()
                 << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        if(pIdx == 0) return nullptr;

        isValid = true;
    } while(isValid == false);

    return p[pIdx-1];



}


void Hero::throwPotion(Potion *p, Entity *e) {
    if (p->isThrowable() == false) {
        cout << ERROR_TAG_START
             << "Cette potion n'est pas jetable!" << endl
             << ERROR_TAG_END << endl;
        return;
    }

    int damageTaked = p->throwOn(e);

    if (damageTaked == -1) {
        cout << ERROR_TAG_START
             << e->getName()
             << " est déjà mort!"
             << endl;
        cout << ERROR_TAG_END << endl;
        return;
    }

    cout << INFO_TAG_START
         << "Vous avez fait " << damageTaked
         << " dégats à " << e->getName()
         << " avec la potion :" << m_name
         << endl;
    cout << INFO_TAG_END << endl;
    this_thread::sleep_for(chrono::seconds(3));
    return;
}

void Hero::usePotion(Potion*p){
    if(p->isThrowable()) {
        delete p;
        return;
    }
    bool deleteAfter = true;
    m_hp += p->getHealRegen();
    if(m_hp > m_maxHp) m_hp = m_maxHp;

    if(p->getDefense() != 0) {
        m_temporaryDefenseItem.push_back(p);
        deleteAfter = false;
    }
    if(p->getAgilityIncrease() != 0) {
        m_temporaryAgilityItem.push_back(p);
        deleteAfter = false;
    }
    if(p->getStrengthIncrease() != 0) {
        m_temporaryStregthItem.push_back(p);
        deleteAfter = false;
    }
    if(deleteAfter == true) delete p;
}

int Hero::getDefense() const {
    int dfs = 0;

    dfs += m_baseDefense;
    for (size_t i =0; i < m_temporaryDefenseItem.size(); i++)
    {
        dfs += m_temporaryDefenseItem[i]->getDefense();
    }

    return dfs;

}

bool Hero::avoidAttack(Damage *dmg) const {
    int percent =0;

    percent += m_baseAgility;

    for(size_t i =0; i < m_temporaryAgilityItem.size(); i++)
    {
        percent *= m_temporaryAgilityItem[i]->getAgilityIncrease()/100;
    }
    if (percent >80) percent = 80;

    percent += m_level - dmg->getLevel();
    percent *= dmg->getAvoidChance()/100;

    srand(time(NULL));
    if (percent > rand()%100) {
        return true;
    }
    return false;
}




Hero::~Hero() {
    for(size_t i =m_temporaryAgilityItem.size()-1; i >= 0; i--){
        delete m_temporaryAgilityItem[i];
    }
    for(size_t i =m_temporaryDefenseItem.size()-1; i >= 0; i--){
        delete m_temporaryDefenseItem[i];
    }
    for(size_t i =m_temporaryStregthItem.size()-1; i >= 0; i--){
        delete m_temporaryStregthItem[i];
    }
}
