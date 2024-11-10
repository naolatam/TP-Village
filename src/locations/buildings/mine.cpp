#include "headers/locations/buildings/mine.h"

Mine::Mine(Game& game): Building(game, "mine") {
    m_level = 1;
    m_difficulty = 1 + rand()%4;
}

void Mine::enter() {
    cout << INFO_TAG_START << endl
         << "Bienvenue dans la mine cher héro!" << endl
         << "Attention, si tu rentres, tu ne pourras pas sortir "
         << "avant d'avoir vaincu tout les monstres! (" << fib(m_level)
         << ")" << endl
         << "Es-tu sur de voulour rentrer? [Y/n]";
    string choice;
    cin >> choice;
    if(choice == "" || choice  == "y" || choice == "Y" || choice == "yes" || choice == "Yes") {
        cout << "Vous décidez donc de rentrer? " << endl
             << "Quel courrage et quel bravoure!" << endl
             << "Voilà ce qu'est un vrai héro!" << endl
             << "Je vous souhaite bon courage :)" << endl;
        this_thread::sleep_for(chrono::seconds(4));
        cout << INFO_TAG_END << endl;
        m_monsterCount= fib(m_level);
        inside();
    }
    else {
        cout << endl << "Tu fais donc demi-tour? Quel dommage..." << endl
             << "J'espère te recroiser bientôt! " << endl
             << "(Tu sors de la mine)" << endl;
        this_thread::sleep_for(chrono::milliseconds(2500));
        cout << INFO_TAG_END << endl;
        Utils::clearTerminal();
        return;
    }
    return;
}


void Mine::inside() {
    Hero* h = m_game.getHero();
    while (m_monsterCount > 0) {
        Utils::clearTerminal();
        m_actualMonster = generateMonster();
        cout << INFO_TAG_START << endl
             << "OH non! un monstre est apparu!" << endl
             << INFO_TAG_END << endl;
        this_thread::sleep_for(chrono::seconds(2));
        m_actualMonster->introduce();
        this_thread::sleep_for(chrono::seconds(10));
        bool isHeroTurn = true;
        while(m_actualMonster->isAlive() && h->isAlive()){
            Utils::clearTerminal();
            if(isHeroTurn) {
                heroTurn();
                isHeroTurn = !isHeroTurn;
            }else {
                monsterTurn();
                isHeroTurn = !isHeroTurn;
            }
        }
        if(!h->isAlive()) {
            cout << FAIL_TAG_START << endl
                 << "Oh non... tu viens de mourir..." << endl
                 << "Tu as atteri à l'auberge, mais ça t'a couté..."
                 << "beaucoup..."
                 << endl
                 << "Fait attention à ta vie la prochaine fois! "
                 << endl;
            h->setGold(10);
            this_thread::sleep_for(chrono::seconds(4));
            cout << FAIL_TAG_END << endl;
            return;
        }
        if(!m_actualMonster->isAlive()) {
            m_monsterCount -=1;
            m_actualMonster->die(h);
            delete m_actualMonster;
            m_actualMonster = nullptr;
            cout << SUCCESS_TAG_START << endl
                 << "Bravo! tu viens de venir à bout de ce monstre!"
                 << endl
                 << "Il en reste encore " << m_monsterCount
                 << endl;
            this_thread::sleep_for(chrono::seconds(3));
            cout << SUCCESS_TAG_END << endl;
        }

    }
    Utils::clearTerminal();
    cout << SUCCESS_TAG_START << endl
         << "Bravo! tu viens de venir à bout de tout les monstres de la mine!"
         << endl
         << "Tu vas pouvoir retourner à la surface ;)"
         << endl
         << "Mais attention! La mine a gagné un niveau! "
         << endl
         <<"Ce sera plus compliqué la prochaine fois, alors entraine toi bien ;)";
    m_level +=1;
    this_thread::sleep_for(chrono::seconds(4));
    cout << endl << SUCCESS_TAG_END << endl;

    return;
}

int Mine::fib(int number) {
    if(number == 1 || number == 2) return 1;
    return fib(number-1) + fib(number-2);
}


Monster* Mine::generateMonster() {
    int maxHp = 100;
    int gold_min, gold_max, gold;
    int baseDamage, baseDefense, baseAgility;
    int criticalChance, criticalDamage;
    MonsterType mnstrType;
    Element mnstrElem;
    Sword* sw = new Sword("Monster sword", 1,
                          rand() % (5*m_level + 10*m_difficulty), 0, 2, 0);
    Shield* sh = new Shield("Monster shield", 1,
                            rand() % (3*m_level + 7*m_difficulty), 2, 0 );
    maxHp *= (m_difficulty+1)*0.5f; // Increase MaxHP based on Mine difficultie
    maxHp *= 1+(0.02f * m_level); // Increase MaxHP by 2% for each level that the mine have.
    maxHp *= 1+(0.02f * m_game.getHero()->getLevel()); // Increase MaxHP by 2% for each mine level.
    gold_min = 5 + m_level*5; // Increase minimum gold that can be earned by 5 for each mine level. (min = 10)
    // Increase maximum gold that can be earned by 5 for each mine level
    // And increase a new time, based on Mine difficultie
    gold_max = (15 + m_level*5)* (m_difficulty+1)*0.5f;
    gold = gold_min + (rand() % (gold_max - gold_min +1));

    baseDamage= 10;
    baseDamage*= 1.0f + (0.1f * m_level) + (0.5f * m_difficulty);
    baseDamage*=0.9f + (rand() % 4) / 100.0f;

    baseDefense=5;
    baseDefense*= 1.0f + (0.08f * m_level) + (0.4f * m_difficulty);
    baseDefense*=0.9f + (rand() % 4) / 100.0f;

    baseAgility = 0;

    criticalChance = rand()%50;
    criticalDamage = 100 + (rand()%50);

    mnstrType = static_cast<MonsterType>(rand()%6);
    mnstrElem = static_cast<Element>(rand()%static_cast<int>(Element::DEFAULT));


    Monster* mnstr = new Monster(maxHp, maxHp, gold,
                                 baseDamage, baseDefense,
                                 criticalChance, criticalDamage,
                                 baseAgility, sw, sh, mnstrType, mnstrElem
                                 );
    return mnstr;
}

void Mine::showHps() const {
    cout << INFO_TAG_START << endl
         << "Vie du monstre: "
         << m_actualMonster->getHp() << "/" << m_actualMonster->getMaxHp()
         << endl
         << "Vie du héro: "
         << m_game.getHero()->getHp() << "/" << m_game.getHero()->getMaxHp() << endl
         << INFO_TAG_END << endl;
}

void Mine::heroTurn() {
    Utils::clearTerminal();
    showHps();
    cout << "C'est au tour du héro!" << endl;
    int action;
    cout << "[1] Attaquer" << endl
         << "[2] Utiliser une potion" << endl
         << "[3] Lancer une potion" << endl;
    bool isValid = false;
    do {
        cout << "Que veux-tu faire? ";
        cin >> action;
        if(action < 1 || action > 3 || cin.fail()) {
            cout << endl << ERROR_TAG_START << "Nombre invalide!"
                 << " Merci d'entrer un nombre compris entre 1 et 3"
                 << ERROR_TAG_END << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        isValid = true;
    }while(isValid == false);

    Potion *p;
    switch (action) {
    case 1:
        if(m_game.getHero()->attack(m_actualMonster) == -1) {heroTurn();};
        break;
    case 2:
        p = m_game.getHero()->askForAPotion(false);
        if(p == nullptr) {
            this_thread::sleep_for(chrono::seconds(2));
            heroTurn();
        }
        m_game.getHero()->getInventory()->removePotion(p);
        m_game.getHero()->usePotion(p);
        break;
    case 3:
        p = m_game.getHero()->askForAPotion(true);
        if(p == nullptr) {
            this_thread::sleep_for(chrono::seconds(2));
            heroTurn();
        }
        m_game.getHero()->getInventory()->removePotion(p);
        m_game.getHero()->throwPotion(p, m_actualMonster);
        break;

    }


    if (!m_actualMonster->isAlive()) {

        int newGoldAmount = m_game.getHero()->getGold() + m_actualMonster->getGold();
        m_game.getHero()->setGold(newGoldAmount);
        int xp = (m_actualMonster->getMaxHp()/m_game.getHero()->getMaxHp());
        xp *= (1+((m_actualMonster->getLevel() - m_game.getHero()->getLevel())/10));
        if (xp < 0) xp = 1;
        m_game.getHero()->addXp(xp);
        if (m_game.getHero()->getXp() >=100) {
            m_game.getHero()->levelUp();
        }
        cout << INFO_TAG_START << endl
             << "Monstre " << getMonsterTypeName(m_actualMonster->getType())
             << " a succombé a ses blessures!" << endl
             << "Vous récupéré donc \033[33m" << m_actualMonster->getGold()
             << "\033[0m galons d'or!"<< endl
             << "Vous avez aussi gagné " << xp
             << " point(s) d'expérience!"<<endl
             << INFO_TAG_END << endl;
        this_thread::sleep_for(chrono::seconds(4));
    }
}
void Mine::monsterTurn() {
    Utils::clearTerminal();
    showHps();
    cout << "C'est au tour du monstre!" << endl;

    int damageInfliged = m_actualMonster->attack(m_game.getHero());
    this_thread::sleep_for(chrono::seconds(5));

}
