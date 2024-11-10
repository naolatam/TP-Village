#include "headers/entity/monster.h"

void Monster::introduce() const {
    cout << PRESENTATION_TAG_START << endl;
    switch (m_type) {
    case MonsterType::UNDEAD:
        cout << "Bruit : *Grrraaah...* (Je suis un "
             << getMonsterTypeName(m_type) << ")";
        break;
    case MonsterType::SPIDER:
        cout << "Bruit : *Chhh-chhh...* (Je suis une "
             << getMonsterTypeName(m_type) << ")";
        break;
    case MonsterType::SKELETON:
        cout << "Bruit : *Clac-clac-clac...* (Je suis un "
             << getMonsterTypeName(m_type) << ")";
        break;
    case MonsterType::GOBLIN:
        cout << "Bruit : *Hihi-haaah!* (Je suis un "
             << getMonsterTypeName(m_type) << ")";
        break;
    case MonsterType::DEMON:
        cout << "Bruit : *Rooooarrr!* (Je suis un "
             << getMonsterTypeName(m_type) << ")";
        break;
    case MonsterType::GHOST:
        cout << "Bruit : *Wooo-oooh...* (Je suis un "
             << getMonsterTypeName(m_type) << ")";
        break;
    default:
        cout << "Bruit inconnu : *...* (Traduction : Une énigme insondable)";
        break;
    }
    cout << endl;
    cout << "RRRrrroohhhh rwwar crrrrrrr-chhh hhhhiiiccccccccc pppprrrraaa ("
         << "J'ai \033[33m" << m_gold << "\033[0m galons d'or" << endl
         << "Je suis niveaux " << m_level << endl
         << "Je fais " << getDamage() << " de dégats"
         << endl
         << "et j'ai " << getDefense() << " de défense"
         << endl
         << "J'ai actuellement "<< m_hp << "/" << m_maxHp << " PV" << endl
         << "J'ai " << m_criticalChance << "% de chance de dégats critique"
         << "et " << m_criticalDamage << "% de dégats en critique!"
         << endl;
    m_shield->showStats();
    m_sword->showStats();
    cout << PRESENTATION_TAG_END;

    return;
}

int Monster::takeDamage(Damage *dmg) {

    if (avoidAttack(dmg) ==true ) {
        cout << INFO_TAG_START << endl
             << "Monstre " << getMonsterTypeName(m_type)
             << " a esquivé l'attaque!"
             << endl << INFO_TAG_END << endl;
        return 0;
    }

    int dfs = getDefense();
    int damageTaked = dmg->getDamageOnElement(m_elem) - dfs;
    if (m_level - dmg->getLevel() < -10) damageTaked+=10;
    else damageTaked -= m_level - dmg->getLevel();

    if(damageTaked < 0) {
        damageTaked = 0;
    }
    m_hp -= damageTaked;

    return damageTaked;
}

int Monster::attack(Entity *entity)  {

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
         << "Monstre " << getMonsterTypeName(m_type)
         << " a fait " << damageTaked
         << " dégats à " << entity->getName();
    if (critical) cout << " en dégat critique!" << endl;
    else cout << endl;
    cout << INFO_TAG_END << endl;
    delete dmg;
    return 0;
}

int Monster::getDefense() const {
    int dfs = 0;
    dfs += m_baseDefense;
    dfs += m_shield->getDefense();


    return dfs;

}

int Monster::getDamage() const {

    int amount=0;
    amount += m_baseDamage;


    amount += m_sword->getDamage();
    amount += floor((1/3)*m_level);

    return amount;
}

Damage* Monster::getAttackDamage() const {

    Damage *dmg = new Damage();

    int amount=getDamage();
    dmg->setElement(m_elem);
    dmg->setAvoidChance(100);

    if (m_sword != nullptr) {
        amount += m_sword->getDamage();
    }

    dmg->setLevel(m_level);
    dmg->setAmount(amount);

    return dmg;
}

void Monster::insult(Entity *entity) const {
    cout << DIALOG_TAG_START
         << "Monstre " << getMonsterTypeName(m_type) << " à "
         << entity->getName() << endl;
    switch (m_type) {
    case MonsterType::UNDEAD:
        cout << "Je vais te faire pourrir vivant, misérable !";
    case MonsterType::SPIDER:
        cout << "Je te ligoterai dans mes toiles, proie insignifiante !";
    case MonsterType::SKELETON:
        cout << "Tu es plus creux qu'une cage thoracique vide !";
    case MonsterType::GOBLIN:
        cout << "Tête de champignon ! Même une pierre est plus maligne !";
    case MonsterType::DEMON:
        cout << "Misérable mortel, je te réduirai en cendres !";
    case MonsterType::GHOST:
        cout << "Tu es plus transparent que moi, pauvre âme errante !";
    default:
        cout << "Espèce inconnue, tu ne mérites même pas une insulte !";
    }
    cout << endl << DIALOG_TAG_END << endl;
}

void Monster::die(Entity *entity) const {
    cout << DIALOG_TAG_START
         << "Monstre " << getMonsterTypeName(m_type) << " à "
         << entity->getName() << endl;
    switch (m_type) {
    case MonsterType::UNDEAD:
        cout << "Je retournerai à la poussière... mais je reviendrai... encore...";
        break;
    case MonsterType::SPIDER:
        cout << "Mon fil... se coupe... mais mes enfants se vengeront...";
        break;
    case MonsterType::SKELETON:
        cout << "Mes os... retourneront... au silence...";
        break;
    case MonsterType::GOBLIN:
        cout << "Arggh... même... pas juste...!";
        break;
    case MonsterType::DEMON:
        cout << "Les flammes... jamais... ne s'éteignent...!";
        break;
    case MonsterType::GHOST:
        cout << "Je disparais... mais je hanterai... toujours...";
        break;
    default:
        cout << "L'ombre s'éteint... mystérieusement...";
        break;
    }
    cout << endl << DIALOG_TAG_END << endl;
}


Monster::~Monster() {
    delete m_sword;
    delete m_shield;
}
