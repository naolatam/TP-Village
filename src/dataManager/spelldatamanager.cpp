#include "headers/dataManager/spelldatamanager.h"

void SpellDataManager::load() {

    QFile file(QString::fromStdString(m_filePath));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << ERROR_TAG_START << endl
         << "Impossible d'ouvrir le fichier contenant les sorts!" << endl
             << "Des sorts aléatoires seront donc générés!" << endl
             << ERROR_TAG_END << endl;
        return;
    }

    // Read & parse file
    QByteArray fileData = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    file.close();

    if (!jsonDoc.isObject()) {
        cout << ERROR_TAG_START << endl;
        cout << "Le fichier de sort n'est pas valide." << endl
             << ERROR_TAG_END << endl;

        return;
    }

    // Access to Principal JSON Object
    QJsonObject jsonObject = jsonDoc.object();
    QJsonArray jsonSpells = jsonObject["spells"].toArray();

    // Iterate over all sort
    for (const QJsonValue &value : jsonSpells) {
        if (!value.isObject()) continue;
        QJsonObject spellObj = value.toObject();

        if (!spellObj.contains("name") || !spellObj["name"].isString() ||
            !spellObj.contains("element") || !spellObj["element"].isDouble() ||
            !spellObj.contains("minLevel") || !spellObj["minLevel"].isDouble() ||
            !spellObj.contains("damage") || !spellObj["damage"].isDouble() ||
            !spellObj.contains("manaConsumption") || !spellObj["manaConsumption"].isDouble() ||
            !spellObj.contains("avoidChance") || !spellObj["avoidChance"].isDouble() ||
            !spellObj.contains("selectionChance") || !spellObj["selectionChance"].isDouble()) {

            cout << "Erreur: Certains attributs manquent "
                 << "ou sont mal définis dans le fichier de sort" << endl;
            continue;
        }

        // Extraction of all attributes from json
        string name = spellObj["name"].toString().toStdString();
        Element element = static_cast<Element>(spellObj["element"].toInt());
        int minLevel = spellObj["minLevel"].toInt();
        int damage = spellObj["damage"].toInt();
        int manaConsumption = spellObj["manaConsumption"].toInt();
        int avoidChance = spellObj["avoidChance"].toInt();
        int selectionChance  = spellObj["selectionChance"].toInt();

        Spell* s= new Spell(name, element, minLevel, damage, manaConsumption, avoidChance);
        m_values.push_back(s);
        m_proba.push_back(selectionChance );
    }
    this_thread::sleep_for(chrono::seconds(1));
}

Spell* SpellDataManager::getRandomValue() const {
    if(m_proba.empty()) {
        Element elem = static_cast<Element>
            (rand()% static_cast<int>(Element::DEFAULT));
        string name = "sort de " + getElementString(elem);


        return new Spell(name, elem, 1, rand()%1000, rand()%200, 1);
    }
    return m_values[Utils::randomOptionWithProbabilities(m_proba)];
}

Spell* SpellDataManager::getRandomValue(Game& game) const {
    if(m_proba.empty()) {
        Element elem = static_cast<Element>
            (rand()% static_cast<int>(Element::DEFAULT));
        string name = "sort de " + getElementString(elem);

        int level = game.getHero()->getLevel();
        int damage = 20 + rand() % game.getHero()->getDamage()/2;
        int manaConsumption = 5 + rand()%50;

        return new Spell(name, elem, level, damage, manaConsumption, rand()%100);
    }
    Spell* s = m_values[Utils::randomOptionWithProbabilities(m_proba)];

    int generationCount = 0;
    while (generationCount < 5
           && s->getMinLevel() > game.getHero()->getLevel()) {

        s = m_values[Utils::randomOptionWithProbabilities(m_proba)];
        generationCount++;
    }

    return s;
}
