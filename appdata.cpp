#include "appdata.h"

appData::appData()
    : ResourcesDirLocation{QStandardPaths::locate(QStandardPaths::AppDataLocation, QString(), QStandardPaths::LocateDirectory)}
{}


void insertNewPassword(QString name, QString password, QString notes) {



}
