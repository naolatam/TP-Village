#include "headers/entity/entity.h"

Entity::Entity(std::string name, int maxHp, int hp, int gold, int baseDamage, int baseDefence,
       int criticalChance, int criticalDamage, int baseAgility)
    : m_name(name), m_maxHp(maxHp), m_hp(hp), m_gold(gold), m_baseDamage(baseDamage),
    m_baseDefense(baseDefence), m_criticalChance(criticalChance),
    m_criticalDamage(criticalDamage), m_baseAgility(baseAgility) {
    m_inventory = new Inventory(64);
    m_level = 1;
};

void Entity::levelUp() {
    m_level++;
    m_xp %= 100;
    cout << LEVEL_UP_TAG_START << endl
         << "Tu viens d'atteindre le niveau " << m_level << "!"
         << "Felicitation" << endl
         << LEVEL_UP_TAG_END << endl;
}

bool Entity::isCritical() const {
    srand(time(NULL));
    if (m_criticalChance > rand() %100)
    {
        return true;
    }
    return false;
}

void Entity::addHp(int hp) {
    m_hp += hp;
    if (m_hp > m_maxHp)
    {
        m_hp = m_maxHp;
    }
    return;
}

bool Entity::isAlive() const {
    return m_hp>0;
}

int Entity::attack(Entity *entity) {
    int coef = 1;

    if (isCritical())
    {
        coef += m_criticalDamage/100;
    }
    Damage* dmg = new Damage(Element::DEFAULT, m_baseDamage*coef, m_level, 100, 100);
    entity->takeDamage(dmg);
    delete dmg;
    return 0;
}

int Entity::takeDamage(Damage *dmg) {
    int damageTaked = (dmg->getAmount() - m_baseDefense);
    m_hp -= damageTaked;
    return damageTaked;
}

void Entity::insult(Entity *entity) const {
    cout << m_name << " say: You son of a bitch " << entity->getName() << endl;
    return;
}




int Entity::getDamage() const {
    return m_baseDamage;
}

int Entity::getDefense() const {
    return m_baseDefense;
}


bool Entity::avoidAttack(Damage *dmg) const {
    int percent =0;

    percent += m_baseAgility;
    if (percent >80) percent = 80;

    percent += m_level - dmg->getLevel();
    percent *= dmg->getAvoidChance()/100;

    srand(time(NULL));
    if (percent > rand()%100) {
        return true;
    }
    return false;
}

void Entity::introduce() const {
    cout << "Salut! Je suis une entité!" << endl;
    return;
}

Entity::~Entity() {
    delete m_inventory;
}
