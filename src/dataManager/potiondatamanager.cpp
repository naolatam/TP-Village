#include "headers/dataManager/potiondatamanager.h"

void PotionDataManager::load() {
    QFile file(QString::fromStdString(m_filePath));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << ERROR_TAG_START << endl
             << "Impossible d'ouvrir le fichier contenant les potions!" << endl
             << "Des potions aléatoires seront donc générés!" << endl
             << ERROR_TAG_END<< endl;
        return;
    }

    // Read & parse file
    QByteArray fileData = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    file.close();

    if (!jsonDoc.isObject()) {
        cout << ERROR_TAG_START << endl
             << "Le fichier de potion n'est pas valide." << endl
             << ERROR_TAG_END<< endl;

        return;
    }

    // Access to Principal JSON Object
    QJsonObject jsonObject = jsonDoc.object();
    QJsonArray jsonPotions = jsonObject["potions"].toArray();

    // Iterate over all sort
    for (const QJsonValue &value : jsonPotions) {
        if (!value.isObject()) continue;
        QJsonObject potionObj = value.toObject();

        // Extraction of all attributes from json
        string name = potionObj["name"].toString().toStdString();
        string type = potionObj["type"].toString().toStdString();
        Element elem = static_cast<Element>(potionObj["elem"].toInt());
        int level = potionObj["level"].toInt();
        int duration = potionObj["duration"].toInt();
        int manaRegen = potionObj["manaRegen"].toInt();
        int strengthIncrease = potionObj["strengthIncrease"].toInt();
        int damage = potionObj["damage"].toInt();
        int defense = potionObj["defense"].toInt();
        int healRegen = potionObj["healRegen"].toInt();
        int agilityIncrease = potionObj["agilityIncrease"].toInt();
        bool throwable = potionObj["throwable"].toBool();
        int price = potionObj["price"].toInt();
        int selectionChance  = potionObj["selectionChance"].toInt();

        Potion* s= new Potion(name, type, elem, level, duration, manaRegen,
                               strengthIncrease, damage, defense, healRegen,
                               agilityIncrease, throwable, price);
        m_values.push_back(s);
        m_proba.push_back(selectionChance );
    }
    this_thread::sleep_for(chrono::seconds(1));
}


Potion* PotionDataManager::getRandomValue() const {
    if(m_proba.empty()) {
        bool isThrowable = rand()%2 == 0;
        bool isHealPotion = rand()%2 == 0;

        string name;
        if (isThrowable) {
            name = "Potion jetable";
        } else if (isHealPotion) {
            name = "Potion de soin";
        } else {
            name = "Potion standard";
        }

        int duration = 0;
        if (!isThrowable && !isHealPotion) {
            duration = 1 + rand() % 20;
        }

        int healRegen = 0;
        int strengthIncrease = 0;
        int manaRegen = 0;
        int damage = 0;
        int defense = 0;
        int agilityIncrease = 0;
        int price = 50 + rand() % 151;
        Element elem = Element::DEFAULT;
        bool throwable = isThrowable;

        if (isThrowable) {
            damage = 10 + rand()%100;
        } else if (isHealPotion) {
            healRegen = 10 + rand()%40;
        }  else {
            int randomProperty = rand()%4;

            switch (randomProperty) {
            case 0:
                manaRegen = 5 + rand()%10;
                break;
            case 1:
                strengthIncrease = 1 + rand()%5;
                break;
            case 2:
                agilityIncrease = 1 + rand()%5;
                break;
            case 3:
                defense = 5 + rand()%10;
                break;
            }
        }

        int level = 1 + rand()%20;

        return new Potion(name, "potion", elem, level, duration, manaRegen,
                          strengthIncrease, damage, defense,
                          healRegen, agilityIncrease, throwable, price);
    }
    return m_values[Utils::randomOptionWithProbabilities(m_proba)];
}
Potion* PotionDataManager::getRandomValue(Game& game) const {
    if(m_proba.empty()) {
        bool isThrowable = rand()%2 == 0;
        bool isHealPotion = rand()%2 == 0;

        string name;
        if (isThrowable) {
            name = "Potion jetable";
        } else if (isHealPotion) {
            name = "Potion de soin";
        } else {
            name = "Potion standard";
        }

        int duration = 0;
        if (!isThrowable && !isHealPotion) {
            duration = 1 + rand() % 20;
        }

        int healRegen = 0;
        int strengthIncrease = 0;
        int manaRegen = 0;
        int damage = 0;
        int defense = 0;
        int agilityIncrease = 0;
        int price = 50 + rand() % 151;
        Element elem = Element::DEFAULT;
        bool throwable = isThrowable;

        if (isHealPotion) {
            healRegen = game.getHero()->getMaxHp()/ 2
                        + rand() % game.getHero()->getMaxHp()/4;
        } else if (isThrowable) {
            damage = game.getHero()->getDamage()/ 3
                     + rand() % game.getHero()->getDamage()/5;
        } else {
            int randomProperty = rand()%4;

            switch (randomProperty) {
            case 0:
                manaRegen = 5 + rand()%10;
                break;
            case 1:
                strengthIncrease = game.getHero()->getBaseDamage()/ 4
                                   + rand() % game.getHero()->getBaseDamage()/8;
                break;
            case 2:
                agilityIncrease = game.getHero()->getBaseAgility()/ 3
                                  + rand() % game.getHero()->getBaseAgility()/6;
                break;
            case 3:
                defense = game.getHero()->getBaseDefence()/ 3
                          + rand() % game.getHero()->getBaseDefence()/4;
                break;
            }
        }

        int level = game.getHero()->getLevel();

        return new Potion(name, "potion", elem, level, duration, manaRegen,
                          strengthIncrease, damage, defense,
                          healRegen, agilityIncrease, throwable, price);
    }
    return m_values[Utils::randomOptionWithProbabilities(m_proba)];
}
