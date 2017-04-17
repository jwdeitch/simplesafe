#include "appdata.h"
#include "botanwrapper.h"

appData::appData() {}

void insertNewPassword(QString label, QString login, QString password) {



}

bool appData::shouldInitialize() {
    return fs::isDirEmpty(appData::resourcesDirLocation() + "safe");
}

//QString
