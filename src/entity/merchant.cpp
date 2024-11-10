#include "headers/entity/merchant.h"
#include "headers/utils.h"

void Merchant::risePrice(int percent) const {
    vector<Potion*> potions = m_inventory->getPotions();
    for(size_t i=0; i < potions.size(); i++) {
        potions[i]->risePrice(percent);
    }
}

int Merchant::buy(Hero *h) {
    if(m_inventory->getUsedSize() == 0) { return -2;}

    int ptIdx;
    bool isValid = false;
    m_inventory->showPotions(true);
    do {
        cout << "La quelle souhaite tu acheter? ";
        cin >> ptIdx;
        if(cin.fail()) {
            cout << endl;
            cout << ERROR_TAG_START
                 << "Nombre invalide! Merci de faire un choix entre 0 et "
                 << m_inventory->getUsedSize()
                  << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        if(ptIdx == 0) {
            return -1;
        }
        ptIdx -=1;
        // Check if index is in range, if potion can be buyed with level differencies and if Hero have enough gold
        isValid = checkIfPotionIndexIsValid(ptIdx, h);
    }while (isValid == false);
    Utils::clearTerminal();
    Potion *p = m_inventory->getPotion(ptIdx);
    h->setGold(h->getGold() - p->getPrice());
    m_inventory->removePotion(p);
    h->getInventory()->addPotion(p);
    notifySellToObserver(this);
    cout << endl
         << SUCCESS_TAG_START
         << "La potion '" << p->getName() << "' a été acheté par le Héro ("
         << h->getName() << ")"
         << endl << SUCCESS_TAG_END << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return 0;
}

bool Merchant::checkIfPotionIndexIsValid(int ptIdx, Hero *h) const {
    if(ptIdx < 0 || ptIdx > m_inventory->getUsedSize() || cin.fail()) {
        cout << endl;
        cout << ERROR_TAG_START
             << "Nombre invalide! Merci de faire un choix entre 0 et "
             << m_inventory->getUsedSize()
             << ERROR_TAG_END << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return false;
    }
    Potion* p = m_inventory->getPotion(ptIdx);
    if (p->getLevel() > h->getLevel()+10) {
        cout << endl;
        cout << ERROR_TAG_START
             << "Tu n'as pas le niveau requis pour acheter cette potion! ("
             << h->getLevel() << "/"
             << p->getLevel()-10 << ")"
             << ERROR_TAG_END << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return false;
    }

    if (p->getPrice() > h->getGold()) {
        cout << endl;
        cout << ERROR_TAG_START
             << "Tu n'as pas assez d'or pour acheter cette potion! ("
             << h->getGold() << "/"
             << p->getPrice() << ")"
             << ERROR_TAG_END << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return false;
    }
    return true;
}



int Merchant::attack(Entity *entity)  {

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
         << "Marchant (" << m_name << ")"
         << " a fait " << damageTaked
         << " dégats à " << entity->getName();
    if (critical) cout << " en dégat critique!" << endl;
    else cout << endl;
    cout << INFO_TAG_END << endl;
    delete dmg;
    return 0;
}

void Merchant::introduce() const {
    cout << PRESENTATION_TAG_START;
    cout << "Bien le bonjour jeune aventurier! "
         << endl
         << "Je me prénomme " << m_name
         << " et je suis un noble marchant de niveau " << m_level << "!"
         << endl
         << "J'ai " << m_gold << "d'or"
         << endl
         << "Je fais " << getDamage() << "de dégats"
         << endl
         << "et j'ai " << getDefense() << "de défense"
         << endl
         << "J'ai actuellement "<< m_hp << "/" << m_maxHp
         << endl;
    cout << PRESENTATION_TAG_END;
}

int Merchant::takeDamage(Damage *dmg) {
    int damageTaked = dmg->getAmount();
    if (m_level - dmg->getLevel() <= -5) damageTaked/=3;
    else damageTaked *= 0.5;

    damageTaked -= getDefense();

    if(damageTaked < 0) {
        damageTaked = 0;
    }
    m_hp -= damageTaked;
    return damageTaked;
}

void Merchant::insult(Entity *entity) const {
    cout << DIALOG_TAG_START
         << "Marchant (" << m_name << ") à "
         << entity->getName() << endl;
    cout << "Par tous les dieux, même un gobelin saurait "
         << "marchander mieux que toi, pauvre gueux mal dégrossi !";
    cout << endl << DIALOG_TAG_END << endl;
}

int Merchant::getDamage() const {

    int amount=0;
    amount += m_baseDamage;
    amount += floor((1/3)*m_level);

    return amount;
}

int Merchant::getDefense() const {
    return m_baseDefense;
}

Damage* Merchant::getAttackDamage() const {

    Damage *dmg = new Damage();

    int amount=getDamage();
    dmg->setElement(Element::DEFAULT);
    dmg->setAvoidChance(100);


    dmg->setLevel(m_level);
    dmg->setAmount(amount);

    return dmg;
}
