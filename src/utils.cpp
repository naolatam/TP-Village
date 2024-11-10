#include "headers/utils.h"

int Utils::randomOptionWithProbabilities(const std::vector<int>& probabilities) {
    if(probabilities.empty()) return -1;

    // create random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    // Calculate the sum of probabilities
    int sumProb = 0.0;
    for (int p : probabilities) {
        sumProb += p;
    }
    // generate a random number between 0 and sumProb
    std::uniform_real_distribution<> dis(0, sumProb);
    int rnd = dis(gen);

    int cumul = 0;
    for (int i = 0; i < probabilities.size(); ++i) {
        cumul += probabilities[i];
        if (rnd <= cumul) {
            return i;
        }
    }

    return -1;

}

std::vector<std::string> Utils::VILLAGE_NAME = {
    "Willowbrook", "Ashbourne", "Stonefield", "Elmswood", "Foxglove Hollow",
    "Maplehill", "Ravencrest", "Brightwater", "Thornridge", "Silverwood",
    "Mossy Vale", "Briar Glen", "Pinehurst", "Dewstone", "Falcon's Reach",
    "Hollowmere", "Eastford", "Bramblegate", "Windmere", "Goldleaf",
    "Copperhill", "Shadowbrook", "Whispering Pines", "Elderwood", "Northglen",
    "Oakshade", "Frostwick", "Suncrest", "Meadowgrove", "Rosewick",
    "Amberstone", "Hazelpeak", "West Hollow", "Clearbrook", "Autumnvale",
    "Springhaven", "Ironforge", "Mistwood", "Hawkstone", "Emberstead",
    "Cragmoor", "Wildwood", "Birchfield", "Riverside", "Redridge",
    "Thistledown", "Snowheath", "Highwatch", "Wolf's Den", "Longdale"
};

std::vector<std::string> Utils::STAFF_NAME = {
    "Crystal Wand", "Arcane Rod", "Inferno Scepter", "Stormbringer",
    "Staff of Wisdom"
};

std::vector<std::string> Utils::SHIELD_NAME = {
    "Aegis of Valor", "Dragonfire Shield", "Guardian's Bulwark",
    "Stormshield", "Celestial Barrier", "Iron Fortress", "Eternal Ward",
    "Vanguard Shield", "Titan’s Guard", "Mystic Aegis"
};

std::vector<std::string> Utils::SWORD_NAME = {
    "Excalibur", "Blade of Eternity", "Dragon Slayer",
    "Sword of the Ancients", "Shadowfang", "Heaven's Edge", "Frostbite",
    "Sunblade", "Soulrender", "Moonlight Saber"
};


std::map<std::string, std::string> Utils::BUILDING_TYPE_FRENCH_TRANSLATION  {
    {"mine", "Mine"},
    {"hostel", "Hôtel"},
    {"shop", "Magasin"},
    {"forge", "Forge"}
};
