#ifndef APPDATA_H
#define APPDATA_H

#include <QString>
#include <QStandardPaths>
#include "fs.h"

class appData
{
public:
    appData();
    static QString resourcesDirLocation() {
        return QStandardPaths::locate(QStandardPaths::AppDataLocation, QString(), QStandardPaths::LocateDirectory);
    }
    void insertNewPassword(QString label, QString login, QString password);
    static bool shouldInitialize();
};

#endif // APPDATA_H
