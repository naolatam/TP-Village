#ifndef SPELLDATAMANAGER_H
#define SPELLDATAMANAGER_H

class Game;

#include "headers/dataManager/datamanager.h"
#include "headers/spell.h"
#include "headers/game.h"

class SpellDataManager : public DataManager
{
private:
    vector<Spell*> m_values;
    vector<int> m_proba;
public:
    SpellDataManager() : DataManager("./save/spells.json") {};
    SpellDataManager(string filePath) : DataManager(filePath) {};

    vector<Spell*> getValues() const {return m_values;};
    Spell* getRandomValue() const;
    Spell* getRandomValue(Game& game) const;

    void load();
};

#endif // SPELLDATAMANAGER_H
