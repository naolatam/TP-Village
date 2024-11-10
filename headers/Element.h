#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

enum class Element {
    WATER,
    FIRE,
    ICE,
    MAGIC,
    EARTH,
    WIND,
    EXPLOSIVE,
    POISON,
    DEFAULT,
    VOID,
};


enum class ElementResistance {
    WATER = static_cast<int>(Element::ICE),       // Eau est résistante à la Glace
    FIRE = static_cast<int>(Element::WIND),       // Feu est résistant au Vent
    ICE = static_cast<int>(Element::WATER),       // Glace est résistante à l'Eau
    MAGIC = static_cast<int>(Element::EARTH),     // Magie est résistante à la Terre
    EARTH = static_cast<int>(Element::FIRE),      // Terre est résistante au Feu
    WIND = static_cast<int>(Element::MAGIC),      // Vent est résistant à la Magie
    EXPLOSIVE = static_cast<int>(Element::FIRE), // Explosif est résistant au feu
    POISON = static_cast<int>(Element::EXPLOSIVE),// Poison est résistant à l'Explosif
    DEFAULT = static_cast<int>(Element::VOID)     // Cas où le sort serait basique
};

enum class ElementWeakness {
    WATER = static_cast<int>(Element::EARTH),     // Eau est faible contre la Terre
    FIRE = static_cast<int>(Element::WATER),      // Feu est faible contre l'Eau
    ICE = static_cast<int>(Element::FIRE),        // Glace est faible contre le Feu
    MAGIC = static_cast<int>(Element::WIND),      // Magie est faible contre le Vent
    EARTH = static_cast<int>(Element::MAGIC),     // Terre est faible contre la Magie
    WIND = static_cast<int>(Element::ICE),        // Vent est faible contre la Glace
    EXPLOSIVE = static_cast<int>(Element::POISON),// Explosif est faible contre le Poison
    POISON = static_cast<int>(Element::WATER),    // Poison est faible contre l'eau
    DEFAULT = static_cast<int>(Element::VOID)     // Cas où le sort serait basique
};


std::string getElementString(Element elem);

#endif // ELEMENT_H
