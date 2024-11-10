#include "headers/Type.h"

std::string getMonsterTypeName(MonsterType type) {
    switch (type) {
    case MonsterType::DEMON: return "Demon";
    case MonsterType::GHOST: return "Fantôme";
    case MonsterType::GOBLIN: return "Goblin";
    case MonsterType::SKELETON: return "Squelette";
    case MonsterType::SPIDER: return "Araignée";
    case MonsterType::UNDEAD: return "Mort vivant";
    default: return "Unknown";
    }
}
