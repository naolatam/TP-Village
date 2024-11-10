#include "../../headers/starter/gameloader.h"

Game* GameLoader::loadGame() {
    return nullptr;
}

Game* GameLoader::createNewGame() {
    SpellDataManager* sDM = new SpellDataManager();
    PotionDataManager* pDM = new PotionDataManager();
    sDM->load();
    pDM->load();
    Hero* h = HeroCreator::getHero(sDM);

    return new Game(h, *sDM, *pDM);
}
