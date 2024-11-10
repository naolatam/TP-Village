#include "headers/locations/village.h"
#include "headers/game.h"


Village::Village(Game& game, int id) : m_game(game), m_id(id) {
    std::srand(time(NULL));
    std::vector<int> BuildingCountProba = {50, 25, 12, 7, 3, 2, 1};
    m_name = Utils::VILLAGE_NAME[std::rand() % Utils::VILLAGE_NAME.size()];
    m_entranceFees = 15*id;
    m_visited = false;
    for(int i = 0; i < Utils::randomOptionWithProbabilities(BuildingCountProba)+1; i++) {
        m_buildings.push_back(new Mine(m_game));
    }
    for(int i = 0; i < Utils::randomOptionWithProbabilities(BuildingCountProba)+1; i++) {
        m_buildings.push_back(new Hostel(m_game));
    }
    for(int i = 0; i < Utils::randomOptionWithProbabilities(BuildingCountProba)+1; i++) {
        m_buildings.push_back(new Shop(m_game));
    }
    for(int i = 0; i < Utils::randomOptionWithProbabilities(BuildingCountProba); i++) {
        m_buildings.push_back(new Forge(m_game));
    }
}

void Village::enter() {
    Utils::clearTerminal();
    cout << INFO_TAG_START << endl
         << "Bienvenue dans le village: " << m_name
         << " (" << m_id << ")"<< endl
         << "Ici, tu trouveras :  " << endl
         << " - " << getBuildingCountFromType("mine") << " Mine" << endl
         << " - " << getBuildingCountFromType("hostel") << " Hôtel" << endl
         << " - " << getBuildingCountFromType("shop") << " Magasin" << endl
         << " - " << getBuildingCountFromType("forge") <<  " Forge" << endl
         << "La taxe d'entrée est de : " << m_entranceFees
         << " galons d'or" << endl;

    if(m_visited == true) { // most current case in first
        int goldAfterFees = m_game.getHero()->getGold() - m_entranceFees;
        m_game.getHero()->setGold(goldAfterFees);
    }else {
        cout << "Parce que c'est ta première visiste, tu n'auras rien "
             << " a payé cette fois-ci! Mais attention la prochaine fois!"
             << endl;
        m_visited = true;
    }

    this_thread::sleep_for(chrono::seconds(2));
    cout << INFO_TAG_END << endl;
    inside();
    return;
}

void Village::inside() {
    map<string, int> buildingTypeCount;
    int count = 0;
    cout << "\033[5m[Vous êtes au coeur du village]\033[0m"<< endl << endl;
    cout << "Voici les différents endroits où "
         << "tu pourras aller dans ce village : " << endl;
    cout << "[0] Sortir du village" << endl;
    for(Building* b:m_buildings) {
        count ++;
        if(buildingTypeCount.count(b->getType()) == 0) {
            buildingTypeCount[b->getType()] = 0;
        }
        buildingTypeCount[b->getType()] += 1;
        cout << "[" << count << "] "
             << Utils::BUILDING_TYPE_FRENCH_TRANSLATION[b->getType()]
             << " n°" << buildingTypeCount[b->getType()] << endl;
    }

    int bIdx;
    bool isValid = false;

    do {
        cout << "Dans quel bâtiment souhaite-tu aller? ";
        cin >> bIdx;

        if(bIdx < 0 || bIdx > count || cin.fail()) {
            cout << endl << ERROR_TAG_START << "Nombre invalide!"
                 << "Merci d'entrer un nombre compris entre 0 et " << count
                 << endl << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        isValid = true;

    } while(isValid == false);

    Utils::clearTerminal();

    if(bIdx == 0) {
        cout << "Tu sors du village?" << endl
             << "Très bien! On espère te revoir bientôt!";
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }
    m_buildings[bIdx-1]->enter(); // enter into the batiment;
    if(m_game.getHero()->isAlive() == false) {
        for(Building* b:m_buildings) {
            if(b->getType() == "hostel") {
                m_game.getHero()->setHp(m_game.getHero()->getMaxHp());
                b->enter();
                break;
            }
        }
    }
    inside(); // re-do the inside of village method interaction;
    return;
}

int Village::getBuildingCountFromType(string type) {
    int count = 0;

    for(Building* b:m_buildings) {
        if (b->getType() == type) {
            count++;
        }
    }

    return count;
}
