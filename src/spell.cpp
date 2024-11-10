#include "headers/spell.h"

bool Spell::equalsTo(Spell *sp) {
    return (sp->m_name == m_name && sp->m_element == m_element
            && sp->m_damage == m_damage
            && sp->m_manaConsumption == m_manaConsumption);
}
