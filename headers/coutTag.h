#ifndef COUTTAG_H
#define COUTTAG_H

#include <string>

using namespace std::string_literals;

const std::string INFO_TAG_START = "\033[34m[INFO]\033[0m "s;
const std::string INFO_TAG_END = "\033[34m[FIN-INFO]\033[0m"s;

const std::string LEVEL_UP_TAG_START = "\033[34m[LEVEL-UP]\033[0m "s;
const std::string LEVEL_UP_TAG_END = "\033[34m[LEVEL-UP-FIN]\033[0m"s;


const std::string PRESENTATION_TAG_START = "\033[34m[Presentation]\033[0m "s;
const std::string PRESENTATION_TAG_END = "\033[34m[FIN-Presentation]\033[0m"s;


const std::string DIALOG_TAG_START = "\033[34m[Dialog]\033[0m "s;
const std::string DIALOG_TAG_END = "\033[34m[FIN-Dialog]\033[0m"s;


const std::string ERROR_TAG_START = "\033[31m[ERREUR]\033[0m "s;
const std::string ERROR_TAG_END = "\033[31m[FIN-ERREUR]\033[0m"s;

const std::string FAIL_TAG_START = "\033[31m[FAIL]\033[0m "s;
const std::string FAIL_TAG_END = "\033[31m[FIN-FAIL]\033[0m"s;


const std::string SUCCESS_TAG_START = "\033[32m[SUCCES]\033[0m "s;
const std::string SUCCESS_TAG_END = "\033[32m[FIN-SUCCES]\033[0m"s;


#endif // COUTTAG_H
