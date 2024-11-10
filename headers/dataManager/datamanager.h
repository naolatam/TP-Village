#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <vector>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <thread>

#include "headers/utils.h"


using namespace std;

class DataManager
{
protected:
    string m_filePath;
public:
    DataManager(string filePath): m_filePath(filePath) {};

    string getFilePath() const {return m_filePath;};
    void setFilePath(string newFilePath) {m_filePath = newFilePath;};

    virtual void load() = 0;
};

#endif // DATAMANAGER_H
