#ifndef APPDATA_H
#define APPDATA_H

#include <QString>
#include <QStandardPaths>
#include "fs.h"
#include "botanwrapper.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

namespace constants {
    const QString SALT = "A2{479-?Wyz?HQaM8>";
}

class appData
{
public:
    appData(QString password);
    static QString resourcesDirLocation() {
        QString path = QStandardPaths::locate(QStandardPaths::AppDataLocation, QString(), QStandardPaths::LocateDirectory);
        return path.left(path.length() - 1) + "safe/";
    }
    QString insertNewPassword(QString label, QString login, QString password, QString filename=NULL);
    static bool shouldInitialize();
    void setMasterPassword(QString password);
    void writeSettings(int cbReset, int lockReset);
    QJsonObject readSettings();
    bool doSettingsExist();
    bool checkMasterPassword(QString password);
    QJsonObject retrievePasswordContents(QString path);
    BotanWrapper botan;
};

#endif // APPDATA_H
