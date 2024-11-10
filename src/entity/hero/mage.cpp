#include "headers/entity/hero/mage.h"


void Mage::introduce() const {
    int activeEffectCount = m_temporaryStregthItem.size()
    + m_temporaryDefenseItem.size()
        + m_temporaryAgilityItem.size();
    string staffName;
    cout << PRESENTATION_TAG_START;
    cout << "Salut! Je me prénomme " << m_name
         << " et je suis un mage!" << endl
         << "J'ai " << m_gold << "d'or" << endl
         << "Je suis niveaux" << m_level << endl
         << "Je fais " << getDamage() << "de dégats"
         << endl
         << "et j'ai " << getDefense() << "de défense"
         << endl
         << "J'ai actuellement "<< m_hp << "/" << m_maxHp << endl
         << "J'ai aussi " << activeEffectCount
         << "effets actif!" << endl
         << "Mon mana s'élève actuellement à "
         << m_mana << "/" << m_manaMax << endl
         << "J'ai " << m_criticalChance << "% de chance de dégats critique"
         << "et " << m_criticalDamage << "% de dégats en critique!"
         << endl;
    m_staff->showStats();
    cout << PRESENTATION_TAG_END;

    return;
}

void Mage::insult(Entity *entity) const {
    cout << DIALOG_TAG_START
         << "Mage à " << entity->getName()
         << endl;
    cout << "Insecte sans magie, même un sort d'illusion te réduirait "
         << "en cendres avant que tu ne comprennes "
         << "ce qui t'a frappé." << endl;
    cout << DIALOG_TAG_END << endl;
}


void Mage::removeEquipementBonus() {
    if(m_isEquipementBonusActived == true) {
        if (m_staff != nullptr) {
            m_manaMax -= m_staff->getManaIncrement();
            m_freeHandsNb += m_staff->getTakingHandNumber();
        };
        m_isEquipementBonusActived = false;
    }
    return;
}

void Mage::addEquipementBonus() {
    if(m_isEquipementBonusActived == false) {
        if(m_staff != nullptr) {
            m_manaMax += m_staff->getManaIncrement();
            m_freeHandsNb -= m_staff->getTakingHandNumber();
            m_isEquipementBonusActived = true;
        }
    }
    return;
}

int Mage::takeDamage(Damage *dmg) {

    if (avoidAttack(dmg) ==true ) {
        cout << INFO_TAG_START << endl
             << m_name << " a esquivé l'attaque!"
             << endl << INFO_TAG_END << endl;
        return 0;
    }

    int dfs = getDefense();
    int damageTaked = dmg->getDamageOnElement(m_element) - dfs;
    if (m_level - dmg->getLevel() < -10) damageTaked+=10;
    else damageTaked -= m_level - dmg->getLevel();

    if(damageTaked < 0) {
        damageTaked = 0;
    }
    m_hp -= damageTaked;
    return damageTaked;
}

int Mage::attack(Entity *entity)  {
    regenMana();
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


int Mage::getDamage() const {


    int amount=0;
    amount += m_baseDamage;
    for (size_t i =0; i < m_temporaryStregthItem.size(); i++)
    {
        amount += m_temporaryStregthItem[i]->getStrengthIncrease();
    }

    amount += floor((1/3)*m_level);

    return amount;
}

Damage* Mage::getAttackDamage()  {

    Damage *dmg = new Damage();

    int amount=getDamage();
    int manaUse =0;

    if (m_staff != nullptr) {
        int spellToUse = askForASpell();
        if (spellToUse ==-1) return new Damage(-1);
        Spell *sp = m_staff->getSpells()[spellToUse-1];
        dmg->setElement(sp->getElement());
        dmg->setSpell(sp);
        dmg->setAvoidChance(sp->getAvoidChance());
        amount += sp->getDamage();
        if (sp->getElement() == m_element) {
            manaUse = sp->getManaConsumption() *0.85; // Use 15% less mana
            amount *=1.05;                            // Make 5% more damage
            dmg->setAvoidChance(sp->getAvoidChance()*0.95); // Decrease avoid chance by 5%
        }
    }

    useMana(manaUse);

    dmg->setLevel(m_level);
    dmg->setAmount(amount);

    return dmg;
}

void Mage::setStaff(Staff *staff, bool deleteActual) {
    removeEquipementBonus();
    if(deleteActual == true && m_staff != nullptr) {
        delete m_staff;
        m_staff= NULL;
    }
    if(m_freeHandsNb < staff->getTakingHandNumber()) {return;};

    m_staff = staff;
    addEquipementBonus();

    return;
}

int Mage::askForASpell() const {
    if (m_staff == nullptr) return -2;
    if (m_staff->getSpells().size() == 1) {
        if (checkIfSpellIsUsable(m_staff->getSpells()[0]) == false) return -1;
        return 1;
    }

    bool valid= false;
    int spellToUse;

    do {
        m_staff->showSpells(true);

        cout << "Merci de choisir un sort à utiliser: ";
        cin >> spellToUse;

        if (spellToUse == 0) return -1;
        if (spellToUse > m_staff->getSpells().size()) continue;
        if (spellToUse < 0) continue;

        if (checkIfSpellIsUsable(m_staff->getSpells()[spellToUse-1])== false) continue;

        valid =true;

    } while (valid == false);

    return spellToUse;

}

bool Mage::checkIfSpellIsUsable(Spell *sp) const {
    if (sp->getMinLevel() > m_level) {
        cout << endl;
        cout << ERROR_TAG_START
             << "Tu n'as pas le niveau requis pour utiliser ce sort! ("
             << sp->getMinLevel() << "/"
             << m_level << ")"
             << endl << ERROR_TAG_END << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return false;
    }

    if (sp->getManaConsumption() > m_mana) {
        cout << endl;
        cout << ERROR_TAG_START
             << "Tu n'as pas assez de mana pour utiliser ce sort! ("
             << sp->getManaConsumption() << "/"
             << m_mana << ")"
             << endl << ERROR_TAG_END << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return false;
    }
    return true;
}

void Mage::regenMana() {
    m_mana *= m_manaRegen/100;
    if (m_mana > m_manaMax) {
        m_mana = m_manaMax;
    }
    return;
}
void Mage::regenMana(int regenMana) {
    if (m_mana + regenMana < m_manaMax) {
        m_mana += regenMana;
    }else {
        m_mana = m_manaMax;
    }
    return;
}

void Mage::createAndAssignDefaultStaff() {
    m_staff = NULL;
    m_staff = new Staff("Sceptre en bois", 1, 5, 0,2);

    addEquipementBonus();
}


void Mage::usePotion(Potion*p){
    if(p->isThrowable()) {
        delete p;
        return;
    }

    bool deleteAfter = true;

    m_mana += p->getManaRegen();
    m_hp += p->getHealRegen();

    if(m_mana > m_manaMax) m_mana = m_manaMax;
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


Mage::~Mage() {
    delete m_staff;
}


