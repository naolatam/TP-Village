#include "headers/game.h"
#include "headers/locations/village.h"


Game::Game(Hero* hero, SpellDataManager& spellDataManager,
           PotionDataManager& potionDataManager) :
    m_hero(hero), m_spellsManager(spellDataManager),
    m_potionsManager(potionDataManager) {

    createVillage();
    cout << "Game initialized" << endl;
}

void Game::createVillage() {

    Village* v = new Village(*this, m_villages.size());
    m_villages.push_back(v);
}

void Game::Play() {
    m_villages[0]->enter();
    int lastVisitedVillage = 0;
    while(m_running) {
        Utils::clearTerminal();
        int newVillageDiscoveringCost = 10 * m_villages.size();
        cout << DIALOG_TAG_START << endl;
        cout << "Bienvenue dans la pampa mon ami!" << endl
             << "Tu es en dehors de tout village! A toi de choisir "
             << "si tu veux arrêter de jouer, explorer pour trouver un nouveau"
             << " village," << endl
             << "ou bien si tu souhaites simplement"
             << " retourner dans un village connu!" << endl
             << DIALOG_TAG_END << endl
             << "En attendant, voici la liste des options possibles:" << endl;

        cout << "[0] Retourner dans le dernier village visité!" << endl;

        int count = 1;
        for(Village* v:m_villages) {
            cout << "[" << count << "] " << "Aller au village: "
                 << v->getName() << " (ID: " << v->getId() << ") (" << "TAXE: "
                 << v->getEntranceFees() << ")" << endl;
            count++;
        }
        cout << "[" << count << "] Explorer! "
             << "(Prix: " << newVillageDiscoveringCost << ")" << endl;
        cout << "[" << count +1 << "] Fermer le jeu" << endl;

        int choice;
        bool isValid;

        do {
            cout << "Que souhaite-tu faire alors? ";
            cin >> choice;

            if(choice < 0 || choice > count+1) {
                cout << endl << ERROR_TAG_START << "Nombre invalide!"
                     << "Merci d'entrer un nombre compris entre 0 et "
                     << count+1 << endl << ERROR_TAG_END << endl;
                this_thread::sleep_for(chrono::seconds(2));
                continue;
            }

            isValid = true;

        } while(isValid == false);
         // i use if instead of switch, because switch doesn't work with
        // I tried to sort statement in DESC from most courant to less
        if(choice == count) {
            if(m_hero->getGold() < newVillageDiscoveringCost) {
                cout << endl << ERROR_TAG_START << "Pas assez d'or!" << endl
                     << "Tu n'as pas assez d'or"
                     << " pour partir découvrir un nouveau village!" << endl
                     << "(" << m_hero->getGold()
                     << "/" << newVillageDiscoveringCost << ")" << endl
                     << ERROR_TAG_END << endl;
                this_thread::sleep_for(chrono::seconds(2));
                continue;
            }
            createVillage();
            m_villages.back()->enter();
            continue;
        } else if(choice == 0) {
            int fees = m_villages[lastVisitedVillage]->getEntranceFees();
            m_hero->setGold(m_hero->getGold() + fees); // If you don't go anywhere, you can reenter in the last village visited for free!

            m_villages[lastVisitedVillage]->enter();
            continue;
        } else if(choice == count +1) {
            m_running = false;
            Utils::clearTerminal();
            cout << INFO_TAG_START << endl;
            cout << "Fermeture du jeu en cours..." << endl;
            cout << " - Sauvegarde du joueur (non implémenté)" << endl;
            cout << " - Sauvegarde des villages (non implémenté" << endl;
            cout << " - Fin" << endl;
            delete m_hero;
            cout << INFO_TAG_END;
            this_thread::sleep_for(chrono::milliseconds(450));
            break;
        } else {
            Village* v = m_villages[choice -1];
            if(m_hero->getGold() < v->getEntranceFees()
                && choice -1 != lastVisitedVillage) {

                cout << endl << ERROR_TAG_START << "Pas assez d'or!" << endl
                     << "Tu n'as pas assez d'or"
                     << " pour payer la taxe d'entrée de ce village!" << endl
                     << "(" << m_hero->getGold()
                     << "/" << v->getEntranceFees() << ")" << endl
                     << ERROR_TAG_END << endl;
                this_thread::sleep_for(chrono::seconds(2));
                continue;

            }
            if(choice -1 == lastVisitedVillage) {
                m_hero->setGold(m_hero->getGold() + v->getEntranceFees()); // If you don't go anywhere, you can reenter in the last village visited for free!
            }
            lastVisitedVillage = choice-1;
            v->enter();
        }
    };

}
