#ifndef TYPE_H
#define TYPE_H

#include <string>

enum class MonsterType {
    UNDEAD,
    SPIDER,
    SKELETON,
    GOBLIN,
    DEMON,
    GHOST
};

std::string getMonsterTypeName(MonsterType type);

#endif // TYPE_H
