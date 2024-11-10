#include "headers/locations/buildings/forge.h"

Forge::Forge(Game& game) : Building(game, "forge") {
    srand(time(NULL));

    m_priceCoef = (100 + (rand()% 50));
    m_luckBonus = rand() % 30;
    return;
}

void Forge::enter() {
    Utils::clearTerminal();
    cout << INFO_TAG_START << endl
         << "Bienvenue dans la forge!" << endl
         << "Ici, tu peux acheter des equipements! " << endl
         << "Et les améliorer bien sur!" << endl;
    cout << INFO_TAG_END << endl;
    this_thread::sleep_for(chrono::seconds(2));

    if(dynamic_cast<Mage*>(m_game.getHero()) != nullptr) {
        insideForMage();
    }
    if(dynamic_cast<Paladin*>(m_game.getHero())) {
        insideForPaladin();
    }
    if(dynamic_cast<Warrior*>(m_game.getHero())) {
        insideForWarrior();
    }
    return;
}

void Forge::insideForMage() {
    Mage* m = dynamic_cast<Mage*>(m_game.getHero());
    Staff* s;
    int price;
    vector<int> staffInSaleProba = {70+m_luckBonus, 30+m_luckBonus};
    bool isThereAStaffInSale =
        Utils::randomOptionWithProbabilities(staffInSaleProba) == 1? true:false;

    if(isThereAStaffInSale == true) {
        int baseDamage, manaIncrement;
        baseDamage = 10 * m->getLevel() / 2;
        baseDamage += rand() % 60*(1 + exp(-m->getLevel()));
        manaIncrement = 25 + m->getLevel();
        manaIncrement += rand() % 50;
        price = (baseDamage + manaIncrement)/10
                + rand() % 100;
        price *= m_priceCoef/100;
        s = new Staff(Utils::STAFF_NAME[baseDamage%5], 1+rand()%2, baseDamage, manaIncrement, rand()%25);

    }

mageInside:
    cout << "\033[5m[Vous êtes dans une forge]\033[0m" << endl << endl;
    cout << "Coef. prix: " << m_priceCoef/100 << "." << m_priceCoef%100 << endl
         << "Bonus de chance: " << m_luckBonus << endl
         << "Tu as \033[33m" << m_game.getHero()->getGold() << "\033[0m galons d'or" << endl;

    cout << "[1] Retour" << endl
         << "[2] Ameliorer le batôn magique" << endl
         << "[3] Inséré de nouveau sort dans le batôn magique" << endl;

    if(isThereAStaffInSale) {
        cout << "[4] Acheter un nouveau batôn magique" << endl;
    }

    int choice;
    bool isValid = false;
    string buyChoice;

    do {
        cout << "Que veux-tu faire? ";
        cin >> choice;
        if(choice < 1 || (choice > 3 && isThereAStaffInSale == false)
            || (choice > 4 && isThereAStaffInSale) || cin.fail()) {
            cout << endl << ERROR_TAG_START << "Nombre invalide!"
                 << "Merci de choisir un index compris entre 1 et "
                 << (isThereAStaffInSale?4:3) << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        isValid = true;

    } while(isValid == false);

    switch (choice) {
    case 1:
        break;
    case 2:
        upgradeStaff(m);
        Utils::clearTerminal();
        goto mageInside;
        break;
    case 3:
        newSpellForStaff(m);
        Utils::clearTerminal();
        goto mageInside;
        break;
    case 4:
        if(s == nullptr) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu as déjà acheté ce spectre!"
                 << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            goto mageInside;
            break;
        }
        s->showStats(false);
        if(m->getGold() < price ){
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez de galons d'or pour acheter ce spectre!"
                 << endl
                 << "(Tu t'es fait exclure de la forge)" << endl
                 << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            break;
        }
        cout << "Tu as \033[33m" << m->getGold() << "\033[0m galons d'or"
             << endl;
        cout << "Veux tu acheter ce spectre pour \033[33m"
             << price << "\033[0m galons d'or? [Y/n]";
        cin >> buyChoice;

        if(buyChoice == "" || buyChoice  == "y" || buyChoice == "Y"
            || buyChoice == "yes" || buyChoice == "Yes") {
            isThereAStaffInSale = false;
            m->setGold(m->getGold() - price);
            m->setStaff(s);
            s = nullptr;
            cout << "Le sceptre t'a bien été équipé!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            Utils::clearTerminal();
            goto mageInside;
        }
        cout << "Très bien! Pas de sceptre pour toi donc!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        goto mageInside;
        break;
    default:
        break;
    }



    if(isThereAStaffInSale) {
        delete s;
        s = nullptr;
    }
    Utils::clearTerminal();
    return;
}

void Forge::upgradeStaff(Mage* m) {
    Utils::clearTerminal();
    int damageUpgradePrice = 0, manaIncrementUpgradePrice = 0;
    if( m->getStaff()->getDamageUpgrade() < m->getStaff()->getMaxUpgrade()) {
        damageUpgradePrice =(m->getStaff()->getDamageUpgrade()+1)
        * m->getStaff()->getDamage();
        damageUpgradePrice -= rand() %damageUpgradePrice/4;
        damageUpgradePrice *= m_priceCoef/100;
    }
    if( m->getStaff()->getManaIncrementUpgrade()< m->getStaff()->getMaxUpgrade()) {
        manaIncrementUpgradePrice =(m->getStaff()->getManaIncrementUpgrade()+1)
        * m->getStaff()->getDamage();
        manaIncrementUpgradePrice -= rand() %manaIncrementUpgradePrice/3;
        manaIncrementUpgradePrice *= m_priceCoef/100;
    }
    cout << "Dégats du sceptre: " << m->getStaff()->getDamage() << endl
         << "Mana du sceptre: " << m->getStaff()->getManaIncrement() << endl;
    cout << endl;
    cout << "[1] Retour" << endl;
    cout << "[2] Améliorer les dégats ("
         << m->getStaff()->getDamageUpgrade() << "/"
         << m->getStaff()->getMaxUpgrade() << ") "
         << "(Prix: "<< damageUpgradePrice << ")" << endl;
    cout << "[3] Améliorer le mana ("
         << m->getStaff()->getManaIncrementUpgrade() << "/"
         << m->getStaff()->getMaxUpgrade() << ") "
         << "(Prix: "<< manaIncrementUpgradePrice << ")" << endl;
    int choice;
    bool isValid = false;

    do {
        cout << "Que souhaite tu faire? ";
        cin >> choice;

        if(choice < 1 || choice > 3 || cin.fail()) {
            cout << endl << ERROR_TAG_START << "Nombre invalide! "
                 << "Merci d'entrer un nombre compris entre 1 et 3"
                 << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        isValid = true;
    } while(isValid == false);

    switch (choice) {
    case 1:
        break;
    case 2:
        if(m->getGold() < damageUpgradePrice) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour améliorer "
                 << "les dégats de spectre!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeStaff(m);
            break;
        }
        if(m->getStaff()->getDamageUpgrade() == m->getStaff()->getMaxUpgrade()) {
            cout << endl << ERROR_TAG_START << endl
                 << "Les dégats de ton sceptre ont déjà "
                 << "atteint le niveau maximum!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeStaff(m);
            break;
        }
        cout << "Les dégats de ton sceptre ont été augmenté de "
             << 5*(m->getStaff()->getDamageUpgrade()+1) << endl;

        m->removeEquipementBonus();
        m->setGold(m->getGold() - damageUpgradePrice);
        m->getStaff()->upgradeDamage(5*(m->getStaff()->getDamageUpgrade()+1));
        m->addEquipementBonus();

        this_thread::sleep_for(chrono::seconds(1));
        upgradeStaff(m);
        break;
    case 3:
        if(m->getGold() < manaIncrementUpgradePrice) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour améliorer "
                 << "le mana de ton spectre!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeStaff(m);
            break;
        }
        if(m->getStaff()->getManaIncrementUpgrade() == m->getStaff()->getMaxUpgrade()) {
            cout << endl << ERROR_TAG_START << endl
                 << "Le mana de ton sceptre a déjà "
                 << "atteint le niveau maximum!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeStaff(m);
            break;
        }
        cout << "Le mana de ton sceptre a été augmenté de "
             << 5*(m->getStaff()->getManaIncrementUpgrade()+1) << endl;

        m->removeEquipementBonus();
        m->setGold(m->getGold() - manaIncrementUpgradePrice);
        m->getStaff()->upgradeManaIncrement(5*(m->getStaff()->getManaIncrementUpgrade()+1));
        m->addEquipementBonus();
        this_thread::sleep_for(chrono::seconds(1));
        upgradeStaff(m);
        break;
    }

    return;
}
void Forge::newSpellForStaff(Mage* m) {

    Utils::clearTerminal();

    vector<int> spellCountProba = {70,20,10}; // 2, 3, 4
    int spellCount = Utils::randomOptionWithProbabilities(spellCountProba) + 2;
    int price = 30* m_priceCoef/100;

    cout << "Voici les sorts actuel dans ton sceptre!" << endl;
    m->getStaff()->showSpells(false);

    cout << "[1] Retour" << endl;
    cout << "[2] Changer les sorts "
         << "(Prix: "<< price << ")" << endl;

    int choice;
    bool isValid = false;

    do {
        cout << "Que souhaite tu faire? ";
        cin >> choice;

        if(choice < 1 || choice > 2 || cin.fail()) {
            cout << endl << ERROR_TAG_START << "Nombre invalide! "
                 << "Merci d'entrer un nombre compris entre 1 et 2"
                 << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        isValid = true;
    } while(isValid == false);

    switch (choice) {
    case 1:
        return;
    case 2:
        if(m->getGold() < price) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent "
                 << "pour changer les sorts de ton sceptre!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
        m->setGold(m->getGold() - price);
        m->getStaff()->clearSpells();
        for(int i = 0; i < spellCount; i++) {
            Spell* nSp = m_game.getSpellDataManager().getRandomValue();
            m->getStaff()->addSpell(nSp);
        }
        Utils::clearTerminal();
        cout << "Voici les nouveaux sorts qui ont été ajouté à la place des anciens!" << endl;
        m->getStaff()->showSpells(false);
        this_thread::sleep_for(chrono::seconds(2));
        newSpellForStaff(m);
        break;
    default:
        break;
    }
    return;
}

void Forge::insideForPaladin() {
    Paladin* p = dynamic_cast<Paladin*>(m_game.getHero());
    Sword* sw;
    Shield* sh;

    int priceSw, priceSh;
    vector<int> equipementInSaleProba = {70+m_luckBonus, 30+m_luckBonus};

    bool isThereASwordInSale =
        Utils::randomOptionWithProbabilities(equipementInSaleProba) == 1? true:false;
    bool isThereAShieldInSale =
        Utils::randomOptionWithProbabilities(equipementInSaleProba) == 1? true:false;
    int baseDefense, weigth, baseDamage;

    if(isThereAShieldInSale == true) {
        weigth = 0;
        baseDefense = 8 * p->getLevel() / 2;
        baseDefense += (rand() % 40);
        weigth = 5 + baseDefense/10;
        weigth += (rand() % 30) ;
        priceSh = (baseDefense + weigth)/10
                  + rand() % 100;
        priceSh *= m_priceCoef/100;
        string nameSh = (Utils::SHIELD_NAME.begin()+ baseDefense%5)->data() ;
        sh = new Shield(nameSh, 1, baseDefense, weigth, rand()%25);

    } // Create a random shield
    if(isThereASwordInSale == true) {
        weigth = 0;
        baseDamage = 10 * p->getLevel() / 2;
        baseDamage += rand() % 50*(1 + exp(-p->getLevel()));
        weigth = baseDamage/10;
        weigth += rand() % 10 ;
        priceSw = (baseDamage + weigth)/3
                  + rand() % 100;
        priceSw *= m_priceCoef/100;
        string nameSw = Utils::SWORD_NAME[baseDamage%5];
        sw = new Sword(nameSw, 1, baseDamage, rand()%15,
                       weigth, rand()%25);

    } // Create a random sword

paladinInside:
    cout << "\033[5m[Vous êtes dans une forge]\033[0m" << endl << endl;
    cout << "Coef. prix: " << m_priceCoef/100 << "." << m_priceCoef%100 << endl
         << "Bonus de chance: " << m_luckBonus << endl
         << "Tu as \033[33m" << m_game.getHero()->getGold() << "\033[0m galons d'or" << endl;
    cout << "[1] Retour" << endl
         << "[2] Ameliorer l'épée" << endl
         << "[3] Améliorer le bouclier" << endl;
    cout << "[" << (isThereAShieldInSale?"4":"?") << "]"
         << " Acheter un nouveau bouclier" << endl;
    cout << "[" << (isThereASwordInSale?"5":"?") << "]"
         << " Acheter une nouvelle épée" << endl;


    int choice;
    bool isValid = false;
    string buyChoice;

    do {
        cout << "Que veux-tu faire? ";
        cin >> choice;

        if(choice < 1 || choice > 5  ||
            (choice == 4 && isThereAShieldInSale == false) ||
            (choice == 5 && isThereASwordInSale == false) || cin.fail()){
            cout << endl << ERROR_TAG_START << "Nombre invalide!"
                 << "Merci de choisir un index compris entre 1 et "
                 << 5 - (isThereASwordInSale?0:(isThereAShieldInSale?1:2))
                 << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        isValid = true;

    } while(isValid == false);

    switch (choice) {
    case 1:
        Utils::clearTerminal();
        break;
    case 2:
        upgradeSword(p);
        Utils::clearTerminal();
        goto paladinInside;
        break;
    case 3:
        upgradeShield(p);
        Utils::clearTerminal();
        goto paladinInside;
        break;
    case 4:
        if(sh == nullptr) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu as déjà acheté ce bouclier ou il n'est pas disponible"
                 << endl
                 << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            goto paladinInside;
            break;
        }
        sh->showStats(false);
        if(p->getGold() < priceSh ){
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez de galons d'or pour acheter ce bouclier!"
                 << endl
                 << "(Tu t'es fait exclure de la forge)" << endl
                 << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(3));
            Utils::clearTerminal();
            break;
        }
        cout << "Tu as \033[33m" << p->getGold() << "\033[0m galons d'or" << endl;
        cout << "Veux tu acheter ce bouclier pour \033[33m"
             << priceSh << "\033[0m galons d'or? [Y/n]";
        cin >> buyChoice;

        if(buyChoice == "" || buyChoice  == "y" || buyChoice == "Y"
            || buyChoice == "yes" || buyChoice == "Yes") {
            p->setGold(p->getGold() - priceSh);
            p->setShield(sh);
            sh = nullptr;
            isThereAShieldInSale = false;
            cout << "Le bouclier t'a bien été équipé!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            Utils::clearTerminal();
            goto paladinInside;
            break;
        }
        cout << "Très bien! Pas de bouclier pour toi donc!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        goto paladinInside;
        break;

    case 5:
        if(sw == nullptr) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu as déjà acheté cette épée ou elle n'est pas disponible"
                 << endl
                 << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            goto paladinInside;
            break;
        }
        sw->showStats(false);
        if(p->getGold() < priceSw ){
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez de galons d'or pour acheter cette épée!"
                 << endl
                 << "(Tu t'es fait exclure de la forge)" << endl
                 << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(3));
            Utils::clearTerminal();
            break;
        }
        cout << "Tu as \033[33m" << p->getGold() << "\033[0m galons d'or" << endl;
        cout << "Veux tu acheter cette épée pour \033[33m"
             << priceSw << "\033[0m galons d'or? [Y/n]";
        cin >> buyChoice;

        if(buyChoice == "" || buyChoice  == "y" || buyChoice == "Y"
            || buyChoice == "yes" || buyChoice == "Yes") {
            p->setGold(p->getGold() - priceSw);
            p->setSword(sw);
            sw = nullptr;
            isThereASwordInSale = false;
            cout << "L'épée t'a bien été équipé!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            Utils::clearTerminal();
            goto paladinInside;
            break;
        }
        cout << "Très bien! Pas d'épée pour toi donc!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        goto paladinInside;
        break;
    default:
        break;
    }
    if(isThereAShieldInSale) {
        delete sh;
        sh = nullptr;
    }
    if(isThereASwordInSale) {
        delete sw;
        sw = nullptr;
    }
    return;
}

void Forge::upgradeSword(Paladin* p) {
    Utils::clearTerminal();
    int damageUpgradePrice=0, agilityUpgradePrice=0, weigthUpgradePrice = 0;
    if( p->getSword()->getDamageUpgrade() < p->getSword()->getMaxUpgrade()) {
        damageUpgradePrice =(p->getSword()->getDamageUpgrade()+1)
        * p->getSword()->getDamage();

        if(damageUpgradePrice < 3) damageUpgradePrice=  8;

        damageUpgradePrice -= rand() %damageUpgradePrice/4;
        damageUpgradePrice *= m_priceCoef/100;

        if(damageUpgradePrice < 3) damageUpgradePrice=  8;

    }
    if( p->getSword()->getAgilityIncreaseUpgrade()< p->getSword()->getMaxUpgrade()) {
        agilityUpgradePrice =(p->getSword()->getAgilityIncreaseUpgrade()+1)
        * p->getSword()->getAgilityIncrease();

        if(agilityUpgradePrice < 3) agilityUpgradePrice=  3;
        agilityUpgradePrice -= rand() %agilityUpgradePrice/3;
        agilityUpgradePrice *= m_priceCoef/100;
        if(agilityUpgradePrice < 3) agilityUpgradePrice=  3;

    }
    if( p->getSword()->getWeigthUpgrade() < p->getSword()->getMaxUpgrade()
        && p->getSword()->getWeigth() != 0) {
        weigthUpgradePrice =(p->getSword()->getWeigthUpgrade()+1)
        * p->getSword()->getWeigth();

        if(weigthUpgradePrice < 3) weigthUpgradePrice=  3;
        weigthUpgradePrice -= rand() %weigthUpgradePrice/3;

        weigthUpgradePrice *= m_priceCoef/100;
        if(weigthUpgradePrice < 0) weigthUpgradePrice = 0;
    }

    cout << "Dégats: " << p->getSword()->getDamage()
         << " | Agilité: " << p->getSword()->getAgilityIncrease()
         << " | Poids: " << p->getSword()->getWeigth() << endl;
    cout << "[1] Retour" << endl;
    cout << "[2] Améliorer les dégats ("
         << p->getSword()->getDamageUpgrade() << "/"
         << p->getSword()->getMaxUpgrade() << ")"
         << "(Prix: "<< damageUpgradePrice << ")" << endl;
    cout << "[3] Améliorer l'agilité ("
         << p->getSword()->getAgilityIncreaseUpgrade() << "/"
         << p->getSword()->getMaxUpgrade() << ") "
         << "(Prix: "<< agilityUpgradePrice << ")" << endl;
    cout << "[4] Réduire le poids ("
         << p->getSword()->getWeigthUpgrade() << "/"
         << p->getSword()->getMaxUpgrade() << ") "
         << "(Prix: "<< weigthUpgradePrice << ")" << endl;
    int choice;
    bool isValid = false;

    do {
        cout << "Que souhaite tu faire? ";
        cin >> choice;

        if(choice < 1 || choice > 4 || cin.fail()) {
            cout << endl << ERROR_TAG_START << "Nombre invalide! "
                 << "Merci d'entrer un nombre compris entre 1 et 4"
                 << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        isValid = true;
    } while(isValid == false);

    switch (choice) {
    case 1:
        break;
    case 2:
        if(p->getGold() < damageUpgradePrice) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour améliorer "
                 << "les dégats de ton épée!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            upgradeSword(p);
            break;
        }
        if(p->getSword()->getDamageUpgrade() == p->getSword()->getMaxUpgrade()) {
            cout << endl << ERROR_TAG_START << endl
                 << "Les dégats de ton épée ont déjà "
                 << "atteint le niveau maximum!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeSword(p);
            break;
        }
        cout << "Les dégats de ton épée ont été augmenté de "
             << 5*(p->getSword()->getDamageUpgrade()+1) << endl;
        p->removeEquipementBonus();
        p->setGold(p->getGold() - damageUpgradePrice);
        p->getSword()->upgradeDamage(5*(p->getSword()->getDamageUpgrade()+1));
        p->addEquipementBonus();
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        upgradeSword(p);
        break;
    case 3:
        if(p->getGold() < agilityUpgradePrice) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour améliorer "
                 << "l'agilité de ton épée!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            upgradeSword(p);
            break;
        }
        if(p->getSword()->getAgilityIncreaseUpgrade() == p->getSword()->getMaxUpgrade()
            || p->getSword()->getAgilityIncrease() == 80) {
            cout << endl << ERROR_TAG_START << endl
                 << "L'agilité de ton épée a déjà "
                 << "atteint le niveau maximum!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeSword(p);
            break;
        }
        cout << "L'agilité de ton épée a été augmenté de "
             << 5*(p->getSword()->getAgilityIncreaseUpgrade()+1) << endl;
        p->removeEquipementBonus();
        p->setGold(p->getGold() - agilityUpgradePrice);
        p->getSword()->upgradeAgilityIncrease(5*(p->getSword()->getAgilityIncreaseUpgrade()+1));
        p->addEquipementBonus();
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        upgradeSword(p);
        break;

    case 4:
        if(p->getGold() < weigthUpgradePrice) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour améliorer "
                 << "le poids de ton épée!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            upgradeSword(p);
            break;
        }
        if(p->getSword()->getWeigthUpgrade() == p->getSword()->getMaxUpgrade()
            || p->getSword()->getWeigth() == 0) {
            cout << endl << ERROR_TAG_START << endl
                 << "Le poids de ton épée a déjà "
                 << "atteint le niveau maximum!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeSword(p);
            break;
        }
        cout << "Le poids de ton épée a été diminué de "
             << 5*(p->getSword()->getWeigthUpgrade()+1) << endl;
        p->removeEquipementBonus();
        p->setGold(p->getGold() - agilityUpgradePrice);
        p->getSword()->upgradeWeigth(5*(p->getSword()->getWeigthUpgrade()+1));
        p->addEquipementBonus();
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        upgradeSword(p);
        break;
    }

    Utils::clearTerminal();
    return;
}
void Forge::upgradeShield(Paladin* p) {
    Utils::clearTerminal();
    cout << "Défense: " << p->getShield()->getDefense()
         << " | Poids: " << p->getShield()->getWeigth() << endl;

    int defenseUpgradePrice=0, weigthUpgradePrice = 0;
    if( p->getShield()->getDefenseUpgrade()!= p->getShield()->getMaxUpgrade()) {
        defenseUpgradePrice =(p->getShield()->getDefenseUpgrade()+1)
        * p->getShield()->getDefense();
        if(defenseUpgradePrice < 4) defenseUpgradePrice = 8;
        defenseUpgradePrice -= rand() %defenseUpgradePrice/4;
        defenseUpgradePrice *= m_priceCoef/100;
        if(defenseUpgradePrice < 0) defenseUpgradePrice = 0;

    }

    if( p->getShield()->getWeigthUpgrade()!= p->getShield()->getMaxUpgrade()
        && p->getShield()->getWeigth() != 0) {
        weigthUpgradePrice =(p->getShield()->getWeigthUpgrade()+1)
        * p->getShield()->getWeigth();

        if(weigthUpgradePrice < 3) weigthUpgradePrice=  3;
        weigthUpgradePrice -= rand() %weigthUpgradePrice/3;

        weigthUpgradePrice *= m_priceCoef/100;
        if(weigthUpgradePrice < 0) weigthUpgradePrice = 0;
    }
    cout << "[1] Retour" << endl;
    cout << "[2] Améliorer la défense ("
         << p->getShield()->getDefenseUpgrade() << "/"
         << p->getShield()->getMaxUpgrade() << ")"
         << "(Prix: "<< defenseUpgradePrice << ")" << endl;
    cout << "[3] Réduire le poids ("
         << p->getShield()->getWeigthUpgrade() << "/"
         << p->getShield()->getMaxUpgrade() << ") "
         << "(Prix: "<< weigthUpgradePrice << ")" << endl;
    int choice;
    bool isValid=false;

    do {
        cout << "Que souhaite tu faire? ";
        cin >> choice;

        if(choice < 1 || choice > 3 || cin.fail()) {
            cout << endl << ERROR_TAG_START << "Nombre invalide! "
                 << "Merci d'entrer un nombre compris entre 1 et 3"
                 << endl << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        isValid = true;
    } while(isValid == false);

    switch (choice) {
    case 1:
        return;
    case 2:
        if(p->getGold() < defenseUpgradePrice) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour améliorer "
                 << "la défense de ton bouclier!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            upgradeShield(p);
            break;
        }
        if(p->getShield()->getDefenseUpgrade() == p->getShield()->getMaxUpgrade()) {
            cout << endl << ERROR_TAG_START << endl
                 << "La défense de ton bouclier a déjà "
                 << "atteint le niveau maximum!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeShield(p);
            break;
        }
        cout << "La défense de ton bouclier a été augmenté de "
             << 5*(p->getShield()->getDefenseUpgrade()+1) << endl;
        p->removeEquipementBonus();
        p->setGold(p->getGold() - defenseUpgradePrice);
        p->getShield()->upgradeDefense(5*(p->getShield()->getDefenseUpgrade()+1));
        p->addEquipementBonus();
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        upgradeShield(p);
        break;
    case 3:
        if(p->getGold() < weigthUpgradePrice) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour améliorer "
                 << "le poids de ton bouclier!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            upgradeShield(p);
            break;
        }
        if(p->getShield()->getWeigthUpgrade() == p->getShield()->getMaxUpgrade()
            || p->getShield()->getWeigth() == 0) {
            cout << endl << ERROR_TAG_START << endl
                 << "Le poids de ton bouclier a déjà "
                 << "atteint le niveau maximum!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeShield(p);
            break;
        }
        cout << "Le poids de ton bouclier a été diminué de "
             << 5*(p->getShield()->getWeigthUpgrade()+1) << endl;
        p->removeEquipementBonus();
        p->setGold(p->getGold() - weigthUpgradePrice);
        p->getShield()->upgradeWeigth(5*(p->getShield()->getWeigthUpgrade()+1));
        p->addEquipementBonus();
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        upgradeShield(p);
        break;
    }

    return;
}

void Forge::insideForWarrior() {
    Warrior* w = dynamic_cast<Warrior*>(m_game.getHero());
    Sword* sw;
    int priceSw;
    vector<int> equipementInSaleProba = {70+m_luckBonus, 30+m_luckBonus};

    bool isThereASwordInSale =
        Utils::randomOptionWithProbabilities(equipementInSaleProba) == 1? true:false;

    if(isThereASwordInSale == true) {
        int baseDamage, weigth;
        baseDamage = 10 * w->getLevel() / 2;
        baseDamage += rand() % 50*(1 + exp(-w->getLevel()));
        weigth = baseDamage/10;
        weigth += rand() % 10 ;
        priceSw = (baseDamage + weigth)/3
                  + rand() % 100;
        priceSw *= m_priceCoef/100;
        sw = new Sword(Utils::SWORD_NAME[baseDamage%5], 1 + rand()%2, baseDamage,
                       rand()%15, weigth, rand()%25);
    } // Create a random sword

warriorInside:
    cout << "\033[5m[Vous êtes dans une forge]\033[0m" << endl << endl;
    cout << "Coef. prix: " << m_priceCoef/100 << "." << m_priceCoef%100 << endl
         << "Bonus de chance: " << m_luckBonus << endl
         << "Tu as \033[33m" << m_game.getHero()->getGold() << "\033[0m galons d'or" << endl;

    cout << "[1] Retour" << endl
         << "[2] Ameliorer l'épée" << endl;
    cout << "[" << (isThereASwordInSale?"3":"?") << "]"
         << " Acheter une nouvelle épée" << endl;


    int choice;
    bool isValid = false;
    string buyChoice;

    do {
        cout << "Que veux-tu faire? ";
        cin >> choice;
        if(choice < 1 || choice > 3  || cin.fail() ||
            (choice == 3 && isThereASwordInSale == false)) {
            cout << endl << ERROR_TAG_START << "Nombre invalide!"
                 << "Merci de choisir un index compris entre 1 et "
                 << (3 - (isThereASwordInSale?0:1))
                 << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        isValid = true;

    } while(isValid == false);

    switch (choice) {
    case 1:
        Utils::clearTerminal();
        break;
    case 2:
        upgradeSword(w);
        Utils::clearTerminal();
        goto warriorInside;
        break;
    case 3:
        if(sw == nullptr) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu as déjà acheté cette épée ou elle n'est pas disponible"
                 << endl
                 << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            goto warriorInside;
            break;
        }
        sw->showStats(false);
        if(w->getGold() < priceSw ){
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez de galons d'or pour acheter cette épée!"
                 << endl
                 << "(Tu t'es fait exclure de la forge)" << endl
                 << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(3));
            Utils::clearTerminal();
            break;
        }
        cout << "Tu as \033[33m" << w->getGold() << "\033[0m galons d'or" << endl;
        cout << "Veux tu acheter cette épée pour \033[33m"
             << priceSw << "\033[0m galons d'or? [Y/n]";
        cin >> buyChoice;

        if(buyChoice == "" || buyChoice  == "y" || buyChoice == "Y"
            || buyChoice == "yes" || buyChoice == "Yes") {
            w->setGold(w->getGold() - priceSw);
            w->setSword(sw);
            sw = nullptr;
            isThereASwordInSale = false;
            cout << "L'épée t'a bien été équipé!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            Utils::clearTerminal();
            goto warriorInside;
            break;
        }
        cout << "Très bien! Pas d'épée pour toi donc!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        goto warriorInside;
        break;
    default:
        break;
    }

    if(isThereASwordInSale) {
        delete sw;
        sw = nullptr;
    }
    return;
}

void Forge::upgradeSword(Warrior* w) {
    Utils::clearTerminal();

    int damageUpgradePrice=0, agilityUpgradePrice=0, weigthUpgradePrice = 0;
    if( w->getSword()->getDamageUpgrade() < w->getSword()->getMaxUpgrade()) {
        damageUpgradePrice =(w->getSword()->getDamageUpgrade()+1)
        * w->getSword()->getDamage();

        if(damageUpgradePrice < 3) damageUpgradePrice=  8;

        damageUpgradePrice -= rand() %damageUpgradePrice/4;
        damageUpgradePrice *= m_priceCoef/100;

        if(damageUpgradePrice < 3) damageUpgradePrice=  8;

    }
    if( w->getSword()->getAgilityIncreaseUpgrade()< w->getSword()->getMaxUpgrade()) {
        agilityUpgradePrice =(w->getSword()->getAgilityIncreaseUpgrade()+1)
        * w->getSword()->getAgilityIncrease();

        if(agilityUpgradePrice < 3) agilityUpgradePrice=  3;
        agilityUpgradePrice -= rand() %agilityUpgradePrice/3;
        agilityUpgradePrice *= m_priceCoef/100;
        if(agilityUpgradePrice < 3) agilityUpgradePrice=  3;

    }
    if( w->getSword()->getWeigthUpgrade() < w->getSword()->getMaxUpgrade()
        && w->getSword()->getWeigth() != 0) {
        weigthUpgradePrice =(w->getSword()->getWeigthUpgrade()+1)
        * w->getSword()->getWeigth();

        if(weigthUpgradePrice < 3) weigthUpgradePrice=  3;
        weigthUpgradePrice -= rand() %weigthUpgradePrice/3;

        weigthUpgradePrice *= m_priceCoef/100;
        if(weigthUpgradePrice < 0) weigthUpgradePrice = 0;
    }


    cout << "Dégats: " << w->getSword()->getDamage()
         << " | Agilité: " << w->getSword()->getAgilityIncrease()
         << " | Poids: " << w->getSword()->getWeigth() << endl;
    cout << "[1] Retour" << endl;
    cout << "[2] Améliorer les dégats ("
         << w->getSword()->getDamageUpgrade() << "/"
         << w->getSword()->getMaxUpgrade() << ")"
         << "(Prix: "<< damageUpgradePrice << ")" << endl;
    cout << "[3] Améliorer l'agilité ("
         << w->getSword()->getAgilityIncreaseUpgrade() << "/"
         << w->getSword()->getMaxUpgrade() << ") "
         << "(Prix: "<< agilityUpgradePrice << ")" << endl;
    cout << "[4] Réduire le poids ("
         << w->getSword()->getWeigthUpgrade() << "/"
         << w->getSword()->getMaxUpgrade() << ") "
         << "(Prix: "<< weigthUpgradePrice << ")" << endl;
    int choice;
    bool isValid = false;

    do {
        cout << "Que souhaite tu faire? ";
        cin >> choice;

        if(choice < 1 || choice > 4 || cin.fail()) {
            cout << endl << ERROR_TAG_START << "Nombre invalide! "
                 << "Merci d'entrer un nombre compris entre 1 et 4"
                 << ERROR_TAG_END << endl;
            continue;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }

        isValid = true;
    } while(isValid == false);

    switch (choice) {
    case 1:
        break;
    case 2:
        if(w->getGold() < damageUpgradePrice) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour améliorer "
                 << "les dégats de ton épée!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            upgradeSword(w);
            break;
        }
        if(w->getSword()->getDamageUpgrade() == w->getSword()->getMaxUpgrade()) {
            cout << endl << ERROR_TAG_START << endl
                 << "Les dégats de ton épée ont déjà "
                 << "atteint le niveau maximum!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeSword(w);
            break;
        }
        cout << "Les dégats de ton épée ont été augmenté de "
             << 5*(w->getSword()->getDamageUpgrade() +1)<< endl;
        w->removeEquipementBonus();
        w->setGold(w->getGold() - damageUpgradePrice);
        w->getSword()->upgradeDamage(5*(w->getSword()->getDamageUpgrade()+1));
        w->addEquipementBonus();
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        upgradeSword(w);
        break;
    case 3:
        if(w->getGold() < agilityUpgradePrice) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour améliorer "
                 << "l'agilité de ton épée!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            upgradeSword(w);
            break;
        }
        if(w->getSword()->getAgilityIncreaseUpgrade() == w->getSword()->getMaxUpgrade()
            || w->getSword()->getAgilityIncrease() == 80) {
            cout << endl << ERROR_TAG_START << endl
                 << "L'agilité de ton épée a déjà "
                 << "atteint le niveau maximum!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeSword(w);
            break;
        }
        cout << "L'agilité de ton épée a été augmenté de "
             << 5*(w->getSword()->getAgilityIncreaseUpgrade()+1) << endl;

        w->removeEquipementBonus();
        w->setGold(w->getGold() - agilityUpgradePrice);
        w->getSword()->upgradeAgilityIncrease(5*(w->getSword()->getAgilityIncreaseUpgrade()+1));
        w->addEquipementBonus();
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        upgradeSword(w);
        break;
    case 4:
        if(w->getGold() < weigthUpgradePrice) {
            cout << endl << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour améliorer "
                 << "le poids de ton épée!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            Utils::clearTerminal();
            upgradeSword(w);
            break;        }
        if(w->getSword()->getWeigthUpgrade() == w->getSword()->getMaxUpgrade()
            || w->getSword()->getWeigth() == 0) {
            cout << endl << ERROR_TAG_START << endl
                 << "Le poids de ton épée a déjà "
                 << "atteint le niveau maximum!"
                 << endl << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            upgradeSword(w);
            break;
        }
        cout << "Le poids de ton épée a été diminué de "
             << 5*(w->getSword()->getWeigthUpgrade()+1) << endl;

        w->removeEquipementBonus();
        w->setGold(w->getGold() - agilityUpgradePrice);
        w->getSword()->upgradeWeigth(5*(w->getSword()->getWeigthUpgrade()+1));
        w->addEquipementBonus();
        this_thread::sleep_for(chrono::seconds(1));
        Utils::clearTerminal();
        upgradeSword(w);
        break;
    }

    return;
}
