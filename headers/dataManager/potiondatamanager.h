#ifndef POTIONDATAMANAGER_H
#define POTIONDATAMANAGER_H

class Game;

#include "headers/dataManager/datamanager.h"
#include "headers/potion/potion.h"
#include "headers/game.h"

class PotionDataManager : public DataManager
{
private:
    vector<Potion*> m_values;
    vector<int> m_proba;
public:
    PotionDataManager() : DataManager("./save/potions.json") {};
    PotionDataManager(string filePath) : DataManager(filePath) {};

    vector<Potion*> getValues() const {return m_values;};
    Potion* getRandomValue() const;
    Potion* getRandomValue(Game& game) const;

    void load();
};

#endif // POTIONDATAMANAGER_H
