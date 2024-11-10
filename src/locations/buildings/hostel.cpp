#include "headers/locations/buildings/hostel.h"

Hostel::Hostel(Game& game): Building(game, "hostel") {
    m_basePrice = 12;
    m_basePrice += game.getVillages().size()*2 % (rand()%15);

    m_maxPrice = 50 + game.getVillages().size()*4 % (rand()%50);

    if(m_maxPrice <= m_basePrice) m_maxPrice = m_basePrice*2.5;
    return;
}

void Hostel::enter() {
    Utils::clearTerminal();
    cout << INFO_TAG_START << endl
         << "Bienvenue dans notre hôtel!" << endl
         << "Ici, tu peux dormir pour récupéré toute ta vie! " << endl
         << "Et c'est moins cher que des potions!" << endl;

    this_thread::sleep_for(chrono::seconds(2));
    cout << INFO_TAG_END << endl;
    inside();
    return;
}

void Hostel::inside() {
    cout << "\033[5m[Vous êtes dans un Hôtel]\033[0m" << endl << endl;
    cout << "Votre vie: " << m_game.getHero()->getHp()
         << "/" << m_game.getHero()->getMaxHp() << "PV" << endl ;
    cout << "[1] Sortir" << endl
         << "[2] Dormir" << endl;
    int choice;
    bool isValid = false;
    do {
        cout << "Que veux-tu faire? ";
        cin >> choice;
        if(choice < 1 || choice > 2 || cin.fail()) {
            cout << endl << ERROR_TAG_START<< "Nombre invalide! "
                 <<"Merci d'entrer un nombre compris entre 1 et 2"
                << endl << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        isValid = true;
    } while(isValid == false);

    switch(choice) {
    case 1: return;
    case 2:
        sleep();
        break;
    default:
        break;
    }

    return;

}


void Hostel::sleep() {
    Utils::clearTerminal();
    int missingHp = m_game.getHero()->getMaxHp()
                    - m_game.getHero()->getHp();
    int price = m_basePrice * missingHp/4;
    if(price > m_maxPrice) price = m_maxPrice;
    if(price == 0) price = m_basePrice;

    cout << endl << INFO_TAG_START << endl
         << "Pour dormir ici et récupéré les " << missingHp
         << "PV qu'il te manque, cela te coutera " << price<< endl
         << "Es-tu sur de voulour dormir? [Y/n]";
    string choice;
    cin >> choice;

    if(choice == "" || choice  == "y" || choice == "Y"
        || choice == "yes" || choice == "Yes") {

        if(m_game.getHero()->getGold() < price) {
            cout << endl << INFO_TAG_END << ERROR_TAG_START << endl
                 << "Tu n'as pas assez d'argent pour payer la nuit ici! ("
                 << m_game.getHero()->getGold() << "/" << price << ")"
                 << endl
                 << "(Le gérant t'a mis à la porte!)"
                 << ERROR_TAG_END << endl;
            this_thread::sleep_for(chrono::seconds(2));
            return;
        }
        cout << "Très bien, bonne nuit!" << endl;
        m_game.getHero()->setGold(m_game.getHero()->getGold() - price); // Remove gold from the hero
        m_game.getHero()->addHp(missingHp); // Restore HP to HPMax
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "\033[2m(Tout les PV ont été régénéré)\033[0m" << endl;
        cout << INFO_TAG_END << endl;
        this_thread::sleep_for(chrono::seconds(2));
        Utils::clearTerminal();
        inside();
        return;
    }
    else {
        cout << endl << "Tu ne veux plus dormir? donc demi-tour?"
             << " Quel dommage..." << endl
             << "J'espère te revoir bientôt dans notre hôtel!"<< endl
             << "(Tu sors de l'hôtel)" << endl;
        cout << INFO_TAG_END << endl;
        this_thread::sleep_for(chrono::seconds(4));
        Utils::clearTerminal();
        return;
    }
    return;
}


