#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <stdlib.h>
#include <vector>
#include <random>


class Utils {
private:
    static void clearTerminalOnWindow() {system("cls");};
    static void clearTerminalOnLinux() {system("clear");};
    static void waitForAKeyOnWin() {system("pause");};
    static void waitForAKeyOnLinux() {system("read");};
public:
#if _WIN32 // Detect if it is a Window (not only 32Bit)
    static void clearTerminal() {clearTerminalOnWindow();};
    static void waitForAKeyToBePressed() {waitForAKeyOnWin();};
#elif __linux__ // Detect if it is a Linux (all distro)
    static void clearTerminal() {clearTerminalOnLinux();};
    static void waitForAKeyToBePressed() {waitForAKeyOnLinux();};
#endif

    static int randomOptionWithProbabilities(const std::vector<int>& probabilities);
    static std::vector<std::string> VILLAGE_NAME;

    static std::vector<std::string> STAFF_NAME;

    static std::vector<std::string> SHIELD_NAME;

    static std::vector<std::string> SWORD_NAME;

    static std::map<std::string, std::string> BUILDING_TYPE_FRENCH_TRANSLATION;

};


#endif // UTILS_H
