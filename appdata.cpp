#include "appdata.h"

appData::appData()
    : ResourcesDirLocation{QStandardPaths::locate(QStandardPaths::AppDataLocation, QString(), QStandardPaths::LocateDirectory)}
{}


