#include "headers/starter/herocreator.h"

Hero* HeroCreator::getHero( SpellDataManager* spellDataManager) {

    cout << "Aucune sauvegarde n'est pour le moment implémenté!" <<endl;
    cout << "Il va donc falloir créé un nouveau héro!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    int heroClass = askHeroClass();
    string heroName = askHeroName();
    int heroMaxHp = askHeroMaxHp();
    int heroGold = askHeroGold();
    int heroDamage = askHeroDamage();
    int heroDefense = askHeroDefense();
    int heroCriticalChance = askHeroCriticalChance();
    int heroCriticalDamage = askHeroCriticalDamage();
    int heroAgility =  askHeroAgility();
    int heroManaMax, heroManaRegen;
    Element heroElem;
    if(heroClass == 1) {
        heroManaMax =askHeroManaMax();
        heroManaRegen =askHeroManaRegen();
        heroElem = askHeroElem();
    }
    Utils::clearTerminal();
    cout << "Voilà! Tu as fini la configuration du héro!" << endl
         << "Création en cours..." << endl;

    Mage* m;
    switch (heroClass) {
    case 1:
        m = new Mage(heroName, 2, heroMaxHp, heroMaxHp, heroGold,
                     heroDamage, heroDefense, heroCriticalChance,
                     heroCriticalDamage, heroAgility, heroManaMax,
                     heroManaRegen, heroElem );
        m->getStaff()->addSpell(spellDataManager->getRandomValue());
        m_hero = m;
        break;
    case 2:
        m_hero = new Warrior(heroName, 2, heroMaxHp, heroMaxHp, heroGold,
                             heroDamage, heroDefense, heroCriticalChance,
                             heroCriticalDamage, heroAgility);
        break;
    case 3:
        m_hero = new Paladin(heroName, 2, heroMaxHp, heroMaxHp, heroGold,
                             heroDamage, heroDefense, heroCriticalChance,
                             heroCriticalDamage, heroAgility);
        break;
    default:
        break;
    }
    for(int i = 0; i < 5; i++) {
        Potion* p = new Potion("Potion de soin", "HEALTH_POTION",
                               Element::DEFAULT, 2, 0, 0, 0, 0, 0,
                               heroMaxHp/10, 0, false, 0);
        m_hero->getInventory()->addPotion(p);
    }
    cout << "Hero créé avec succès!" << endl;
    return m_hero;

}

int HeroCreator::askAInt(int min, int max) {
    int choice;
    bool isValid = false;

    do{
        cin >> choice;
        if(choice < min || choice > max || cin.fail()) {
            cout << endl << ERROR_TAG_START << "Nombre invalide!"
                 << "Merci d'entrer un nombre compris entre "
                 << min << " et " << max
                 << endl << ERROR_TAG_END << endl;
            cout << ">>";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        isValid = true;
    } while(isValid ==false);

    return choice;
}

int HeroCreator::askHeroClass() {
    Utils::clearTerminal();
    cout << "Etape 1: Choisir une classe" << endl;
    cout << "[1] Mage (utilise la magie et le mana)" << endl;
    cout << "[2] Guerrier (+50% dégats)" << endl;
    cout << "[3] Paladin (Utilise épée et bouclier)" << endl;
    cout << "Quel classe souhaite-tu incarner? ";
    return askAInt(1,3);
}

string HeroCreator::askHeroName(){
    Utils::clearTerminal();
    cout << "Etape 2: Comment t'appelle tu? " << endl;

    string name;
    getline(cin>> std::ws, name);

    return name;
}

int HeroCreator::askHeroMaxHp(){
    Utils::clearTerminal();
    cout << "Etape 3: Combien as-tu de point de vie? (max: 50000) " << endl;

    return askAInt(1, 50000);
}

int HeroCreator::askHeroGold(){
    Utils::clearTerminal();
    cout << "Etape 4: Combien as-tu de galon d'or sur toi? (max: 50000) " << endl;

    return askAInt(0, 50000);
}

int HeroCreator::askHeroDamage() {
    Utils::clearTerminal();
    cout << "Etape 5: Combien de dégats fait-tu? (max: 50000) " << endl;

    return askAInt(1, 50000);
}
int HeroCreator::askHeroDefense() {
    Utils::clearTerminal();
    cout << "Etape 5: Combien de défense as-tu? (max: 50000) " << endl;

    return askAInt(1, 50000);
}

int HeroCreator::askHeroCriticalChance() {
    Utils::clearTerminal();
    cout << "Etape 6: Combien de pourcentage de coup critique as-tu? "
         << "(max: 100) " << endl;

    return askAInt(0, 100);
}
int HeroCreator::askHeroCriticalDamage() {
    Utils::clearTerminal();
    cout << "Etape 7: Combien de pourcentage de dégats critique as-tu? "
         << "(min: 100) (max: 50000) " << endl;

    return askAInt(100, 50000);
}

int HeroCreator::askHeroAgility() {
    Utils::clearTerminal();
    cout << "Etape 8: Combien d'agilité as-tu? "<< "(max: 80) " << endl;

    return askAInt(0, 80);
}

int HeroCreator::askHeroManaMax() {
    Utils::clearTerminal();
    cout << "Etape 9: Combien de mana as-tu? (min: 100) (max: 50000) " << endl;

    return askAInt(100, 50000);
}

int HeroCreator::askHeroManaRegen() {
    Utils::clearTerminal();
    cout << "Etape 10: Combien de % mana regagne tu à chaque tour? "
         << "(min: 1) (max: 100) " << endl;

    return askAInt(1, 100);
}

Element HeroCreator::askHeroElem() {
    Utils::clearTerminal();
    cout << "Etape 11: Quel sera ton élément? " << endl;
    for (int i = 0; i < static_cast<int>(Element::DEFAULT); ++i) {
        string elementName = getElementString(static_cast<Element>(i));
        std::cout << "[" << i+1 << "]: " << elementName << "\n";
    };
    int idx = askAInt(1, static_cast<int>(Element::DEFAULT)) -1;
    return static_cast<Element>(idx);
}

Hero* HeroCreator::m_hero = nullptr;
