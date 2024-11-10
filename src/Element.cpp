#include "headers/Element.h"

std::string getElementString(Element elem) {
    switch (elem) {
    case Element::WATER:     return "Water";
    case Element::FIRE:      return "Fire";
    case Element::ICE:       return "Ice";
    case Element::MAGIC:     return "Magic";
    case Element::EARTH:     return "Earth";
    case Element::WIND:      return "Wind";
    case Element::EXPLOSIVE: return "Explosif";
    case Element::POISON:    return "Poison";
    case Element::DEFAULT:   return "Default";
    case Element::VOID:      return "Void";
    default:                 return "Unknown Element";
    }
}
