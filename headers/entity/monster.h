#ifndef MONSTER_H
#define MONSTER_H

#include "headers/entity/entity.h"
#include "headers/weapon/sword.h"
#include "headers/weapon/shield.h"
#include "headers/Type.h"

class Monster : public Entity
{

private:
    Sword *m_sword;
    Shield *m_shield;
    MonsterType m_type;
    Element m_elem;

public:
    Monster(int maxHp, int hp, int gold,
            int baseDamage, int baseDefence, int criticalChance,
            int criticalDamage, int baseAgility, Sword *sword,
            Shield *shield, MonsterType type, Element element)
        : Entity("Monstre " + getMonsterTypeName(type), maxHp, hp, gold,
                 baseDamage, baseDefence, criticalChance, criticalDamage,
                 baseAgility), m_sword(sword), m_shield(shield), m_type(type),
        m_elem(element) {};

    ~Monster();

    MonsterType getType() const {return m_type;};
    int getDamage() const;
    int getDefense() const;
    Damage* getAttackDamage() const;

    int attack(Entity *entity);
    void introduce() const;
    int takeDamage(Damage *dmg);
    void insult(Entity *entity) const;
    void die(Entity *entity) const;


};

#endif // MONSTER_H
