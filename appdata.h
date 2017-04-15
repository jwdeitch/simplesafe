#ifndef APPDATA_H
#define APPDATA_H

#include <QString>
#include <QStandardPaths>

class appData
{
public:
    appData();
    const QString & ResourcesDirLocation;
    void insertNewPassword(QString name, QString password, QString notes);
};

#endif // APPDATA_H
