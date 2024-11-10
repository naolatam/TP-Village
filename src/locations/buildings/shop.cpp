#include "headers/locations/buildings/shop.h"

Shop::Shop(Game &game) : Building(game, "shop") {
    std::vector<int> merchantCountProba = {40, 25, 22, 8, 5};
    int merchantCount = Utils::randomOptionWithProbabilities(merchantCountProba)+1;

    for(int i = 0; i < merchantCount+1; i++) {
        int invSize = 10 + rand() % (2 + rand() % 28 );
        Merchant* m = new Merchant("Pedro", 9999, 9999, 1535, 150, 250, 55, 250, 0);
        m->addObserver(this);
        m->getInventory()->setSize(invSize);
        for(int x = 0; x < invSize; x++) {
            m->getInventory()->addPotion(getPotionFromShopStock());
        }
        m_merchants.push_back(m);
    }


}

void Shop::enter() {
    Utils::clearTerminal();
    cout << INFO_TAG_START << endl
         << "Bienvenue dans notre magasin!" << endl
         << "Ici, tu peux acheter des potions! " << endl
         << "Et les revendre bien sur!" << endl;

    this_thread::sleep_for(chrono::seconds(2));
    cout << INFO_TAG_END << endl;
    inside();
    return;
}

void Shop::inside() {
    cout << "\033[5m[Vous êtes dans un Magasin]\033[0m" << endl << endl;
    cout << "Vous disposez de : " << endl
         << "  - \033[33m" << m_game.getHero()->getGold()
         << "\033[0m galons d'or" << endl
         << "  - \033[35m" << m_game.getHero()->getInventory()->getUsedSize()
         << "\033[0m potions" << endl;

    cout << "[1] Sortir" << endl
         << "[2] Acheter des potions" << endl
         << "[3] Vendre des potions" << endl
         << "[4] Voir mes potions" << endl;
    int choice;
    bool isValid = false;

    do {
        cout << "Que veux-tu faire? ";
        cin >> choice;
        if(choice < 1 || choice > 4 || cin.fail()) {
            cout << endl << ERROR_TAG_START<< "Nombre invalide! "
                 <<"Merci d'entrer un nombre compris entre 1 et 4"
                 << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        isValid = true;
    } while(isValid == false);
    string ign;
    switch(choice) {
    case 1: break;
    case 2:
        interactWithMerchant();
        Utils::clearTerminal();
        inside();
        break;
    case 3:
        sellPotion();
        Utils::clearTerminal();
        inside();
        break;
    case 4:
        Utils::clearTerminal();
        cout << "Voici les potions de ton inventaire: "<< endl;
        m_game.getHero()->getInventory()->showPotions();
        cout << INFO_TAG_END << endl;
        Utils::waitForAKeyToBePressed();
        Utils::clearTerminal();
        inside();
        break;
    default:
        break;
    }
    Utils::clearTerminal();
    return;

}

void Shop::interactWithMerchant() {
    Utils::clearTerminal();
    if(m_merchants.size() == 1) {
        interactWithMerchant(0);
        return;
    }
    int count = 0;
    int choice;
    bool isValid = false;
    cout << "[0] Retour" <<endl;

    for(Merchant* m:m_merchants) {
        count++;
        {
            cout << "[" << count << "] Marchant n°" << count << endl;
        }

    }
    do {
        cout << "Avec quel marchant souhaite-tu marchander? ";
        cin >> choice;
        if(choice < 0 || choice > count || cin.fail()) {
            cout << endl << ERROR_TAG_START<< "Nombre invalide! "
                 <<"Merci d'entrer un nombre compris entre 0 et "<< count
                 << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        isValid = true;
    } while(isValid == false);
    Utils::clearTerminal();
    if(choice == 0) return;

    interactWithMerchant(choice-1);
    return;
}

void Shop::interactWithMerchant(int mIdx) {
    if(mIdx > m_merchants.size() -1) {return;}
    Utils::clearTerminal();
    cout << "Voici les potions du marchant n°" << mIdx +1 << endl;
    int statusCodeOfBuyTransaction = m_merchants[mIdx]->buy(m_game.getHero());
    if(statusCodeOfBuyTransaction == -2) {
        cout << endl << ERROR_TAG_START << endl
             << "Ce marchant n'a plus de potion en stock!" << endl
             << ERROR_TAG_END << endl;
        this_thread::sleep_for(chrono::seconds(3));
        return;
    }
    if(statusCodeOfBuyTransaction == -1) {
        return;
    }
    interactWithMerchant(mIdx);

    // Note for Antonico :
    // Je sais que j'aurai pu utiliser le code renvoyé par la fonction buy au lieu de l'observeur,
    // mais au moins, j'utilise un pattern X)
}


void Shop::sellPotion() {
    Utils::clearTerminal();
    bool isValid = false;
    int pIdx;
    int potionCount = m_game.getHero()->getInventory()->getUsedSize();
    m_game.getHero()->getInventory()->showPotions(true);

    do {
        cout << "Quel potion veux-tu vendre? ";
        cin >> pIdx;
        if(pIdx < 0 || pIdx > potionCount || cin.fail()) {
            cout << endl << ERROR_TAG_START << "Index invalide!"
                 << "Merci de choisir un nombre entre 0 et " << potionCount
                 << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        isValid = true;
    } while(isValid == false);

    Utils::clearTerminal();
    if(pIdx == 0) return;
    pIdx -=1;
    Potion* p = m_game.getHero()->getInventory()->getPotion(pIdx);
    string choice;
    cout << "Es-tu sur de voulour revendre : \033[22;5m"
         << p->getName()
         << "\033[0m pour "
         << p->getPrice()/2
         << " galons d'or? [Y/n]";
    cin >> choice;
    if(choice == "" || choice  == "y" || choice == "Y"
        || choice == "yes" || choice == "Yes") {

        cout << "Très bien! "<< endl
             << p->getPrice()/2
             << " gallons d'or viennent de vous être confié" << endl;

        int gold = m_game.getHero()->getGold();
        gold += p->getPrice()/2;
        m_game.getHero()->setGold(gold); // Adding gold
        m_game.getHero()->getInventory()->removePotion(p); // Removing potion
        delete p; // Deleting no more used potion

        cout << INFO_TAG_END << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }
    else {
        cout << "Pas de vente alors? Dommage..." << endl
             << "Veuillez re-regarder vos potions tout de-même" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << INFO_TAG_END << endl;
        sellPotion();
        return;
    }

}

Potion* Shop::getPotionFromShopStock() const {
    return m_game.getPotionManager().getRandomValue();
}

// Method call when observer send a notification for a sell.
// So we need to add a new potion to merchant inventory!
void Shop::notifySell(Merchant* m) {
    m->getInventory()->addPotion(getPotionFromShopStock());
    return;
}


Shop::~Shop() {
    for(Merchant* m:m_merchants) {
        delete m;
    }
}
