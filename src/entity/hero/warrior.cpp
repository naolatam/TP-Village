#include "headers/entity/hero/warrior.h"

void Warrior::createBasicSword() {
    Sword* s = new Sword("Epée en bois", 1, 5, 5, 2, 2);
    m_sword = s;
}

void Warrior::introduce() const {
    int activeEffectCount = m_temporaryStregthItem.size()
    + m_temporaryDefenseItem.size()
        + m_temporaryAgilityItem.size();
    string staffName;
    cout << PRESENTATION_TAG_START;
    cout << "Salut! Je me prénomme " << m_name
         << " et je suis un un guerrier!" << endl
         << "J'ai " << m_gold << "d'or" << endl
         << "Je suis niveaux" << m_level << endl
         << "Je fais " << getDamage() << "de dégats"
         << endl
         << "et j'ai " << getDefense() << "de défense"
         << endl
         << "J'ai actuellement "<< m_hp << "/" << m_maxHp << endl
         << "J'ai aussi " << activeEffectCount
         << "effets actif!" << endl
         << "J'ai " << m_criticalChance << "% de chance de dégats critique"
         << "et " << m_criticalDamage << "% de dégats en critique!"
         << endl;
    m_sword->showStats();
    cout << PRESENTATION_TAG_END;

    return;
}

void Warrior::insult(Entity *entity) const {
    cout << DIALOG_TAG_START
         << "Guerrier à " << entity->getName()
         << endl;
    cout << "Espèce de chien sans honneur, même ton ombre fuit le combat!"
         << endl;
    cout << DIALOG_TAG_END << endl;
}


void Warrior::removeEquipementBonus() {
    if(m_isEquipementBonusActived == true) {
        if(m_sword != nullptr) {
            m_freeHandsNb += m_sword->getTakingHandNumber();
            m_baseAgility += m_sword->getWeigth()/10;
        }
        m_isEquipementBonusActived = false;
    }
}
void Warrior::addEquipementBonus() {
    if(m_isEquipementBonusActived == false) {
        if(m_sword != nullptr) {
            m_freeHandsNb -= m_sword->getTakingHandNumber();
            m_baseAgility -= m_sword->getWeigth()/10;
            m_isEquipementBonusActived = true;
        }
    }
}


int Warrior::takeDamage(Damage *dmg) {

    if (avoidAttack(dmg) ==true ) {
        cout << INFO_TAG_START << endl
             << m_name << " a esquivé l'attaque!"
             << endl << INFO_TAG_END << endl;
        return 0;
    }

    int dfs = getDefense();
    int damageTaked = dmg->getDamageOnElement(Element::DEFAULT) - dfs;
    if (m_level - dmg->getLevel() < -10) damageTaked+=10;
    else damageTaked -= m_level - dmg->getLevel();

    if(damageTaked < 0) {
        damageTaked = 0;
    }
    m_hp -= damageTaked;
    return damageTaked;
}

int Warrior::attack(Entity *entity)  {

    Damage* dmg = getAttackDamage();

    if (dmg->getAmount() == -1) {
        delete dmg;
        return -1;
    }

    bool critical = false;
    if (isCritical())
    {
        critical = true;
        dmg->setAmount(dmg->getAmount() * m_criticalDamage/100);
    }


    int damageTaked = entity->takeDamage(dmg);

    cout << INFO_TAG_START
         << "Vous avez fait " << damageTaked
         << " dégats à " << entity->getName();
    if (critical) cout << " en dégat critique!" << endl;
    else cout << endl;
    cout << INFO_TAG_END << endl;

    delete dmg;

    this_thread::sleep_for(chrono::seconds(2));
    return 0;
}


int Warrior::getDamage() const {

    int amount=0;
    amount += m_baseDamage*1.5;
    for (size_t i =0; i < m_temporaryStregthItem.size(); i++)
    {
        amount += m_temporaryStregthItem[i]->getStrengthIncrease();
    }

    amount += m_sword->getDamage();
    amount += floor((1/3)*m_level);

    return amount;
}

Damage* Warrior::getAttackDamage()  {

    Damage *dmg = new Damage();

    int amount=getDamage();

    if (m_sword != nullptr) {
        dmg->setElement(Element::DEFAULT);
        dmg->setAvoidChance(100);
    }

    dmg->setLevel(m_level);
    dmg->setAmount(amount);

    return dmg;
}

void Warrior::setSword(Sword *sword, bool deleteActual) {

    removeEquipementBonus();

    if(deleteActual == true) delete m_sword;
    if(m_freeHandsNb < sword->getTakingHandNumber()) {return;}

    m_sword = sword;
    addEquipementBonus();

    return;
}

Warrior::~Warrior() {
    delete m_sword;
}

