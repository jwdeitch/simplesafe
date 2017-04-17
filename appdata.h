#ifndef APPDATA_H
#define APPDATA_H

#include <QString>
#include <QStandardPaths>

class appData
{
public:
    appData();
    static QString ResourcesDirLocation() { return QStandardPaths::locate(QStandardPaths::AppDataLocation, QString(), QStandardPaths::LocateDirectory); }
    void insertNewPassword(QString name, QString password, QString notes);
};

#endif // APPDATA_H
