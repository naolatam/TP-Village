#ifndef GAME_H
#define GAME_H

class Village;
class DataManager;
class SpellDataManager;
class PotionDataManager;

#include <vector>

#include "headers/entity/hero/hero.h"
#include "headers/dataManager/spelldatamanager.h"
#include "headers/dataManager/potiondatamanager.h"
#include "headers/utils.h"


class Game
{
private:
    Hero* m_hero;
    vector<Village*> m_villages;
    SpellDataManager& m_spellsManager;
    PotionDataManager& m_potionsManager;
    bool m_running;
public:
    Game(Hero* hero, SpellDataManager& spellDataManager, PotionDataManager& potionDataManager);

    const vector<Village*>& getVillages() const {return m_villages;};
    Hero* getHero() const {return m_hero;};

    void Play();

    PotionDataManager& getPotionManager() {return m_potionsManager;};
    SpellDataManager& getSpellDataManager() {return m_spellsManager;};
    void createVillage();
};

#endif // GAME_H
