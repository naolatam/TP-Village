#include "headers/entity/hero/paladin.h"

void Paladin::createBasicSwordAndShield() {
    Sword* sw = new Sword("Epée en bois", 1, 5, 5, 2, 2);
    Shield* sh = new Shield("Bouclier en bois", 1, 5, 4, 3);
    m_sword = sw;
    m_shield = sh;
    return;
}


void Paladin::introduce() const {
    int activeEffectCount = m_temporaryStregthItem.size()
    + m_temporaryDefenseItem.size()
        + m_temporaryAgilityItem.size();
    cout << PRESENTATION_TAG_START;
    cout << "Salut! Je me prénomme " << m_name
         << " et je suis un paladin!" << endl
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
    m_shield->showStats();
    m_sword->showStats();
    cout << PRESENTATION_TAG_END;

    return;
}

void Paladin::insult(Entity *entity) const {
    cout << DIALOG_TAG_START
         << "Paladin à " << entity->getName()
         << endl;
    cout << "Ton honneur brille autant qu'une bougie éteinte."
         << endl;
    cout << DIALOG_TAG_END << endl;
}

void Paladin::removeEquipementBonus() {
    if(m_isEquipementBonusActived == true) {
        if(m_shield != nullptr ){
            m_freeHandsNb += m_shield->getTakingHandNumber();
            m_baseAgility += m_shield->getWeigth()/10;
        }
        if(m_sword != nullptr){
            m_freeHandsNb += m_sword->getTakingHandNumber();
            m_baseAgility += m_sword->getWeigth()/10;
        }
        m_isEquipementBonusActived = false;
    }
    return;
}
void Paladin::addEquipementBonus() {
    if(m_isEquipementBonusActived == false) {
        if(m_shield != nullptr){
            m_freeHandsNb -= m_shield->getTakingHandNumber();
            m_baseAgility -= m_shield->getWeigth()/10;
        }
        if(m_sword != nullptr) {
            m_freeHandsNb -= m_sword->getTakingHandNumber();
            m_baseAgility -= m_sword->getWeigth()/10;
        }
        m_isEquipementBonusActived = true;
    }
    return;
}

int Paladin::takeDamage(Damage *dmg) {

    if (avoidAttack(dmg) ==true ) {
        cout << INFO_TAG_START << endl
             << m_name << " a esquivé l'attaque!"
             << endl << INFO_TAG_END << endl;
        return 0;
    }

    int dfs = getDefense();
    dfs += m_shield->getDefense();
    int damageTaked = dmg->getDamageOnElement(Element::DEFAULT) - dfs;
    if (m_level - dmg->getLevel() < -10) damageTaked+=10;
    else damageTaked -= m_level - dmg->getLevel();

    if(damageTaked < 0) {
        damageTaked = 0;
    }
    m_hp -= damageTaked;
    return damageTaked;
}

int Paladin::attack(Entity *entity)  {

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


int Paladin::getDamage() const {

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

Damage* Paladin::getAttackDamage()  {

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


void Paladin::setShield(Shield *shield, bool deleteActual) {

    removeEquipementBonus();
    if(deleteActual == true) delete m_shield;
    if(m_freeHandsNb < shield->getTakingHandNumber()) {return;}

    m_shield = shield;
    addEquipementBonus();

    return;
}

void Paladin::setSword(Sword *sword, bool deleteActual){

    removeEquipementBonus();
    if(deleteActual == true) delete m_sword;

    if(m_freeHandsNb < sword->getTakingHandNumber()) {return;}

    m_sword = sword;
    addEquipementBonus();

    return;
}

Paladin::~Paladin() {
    delete m_sword;
    delete m_shield;
}


