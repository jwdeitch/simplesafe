#include "appdata.h"

appData::appData() {}

void insertNewPassword(QString label, QString login, QString password) {



}

static void setMasterPassword(QString password) {
    appData::botan.setPassword(constants::SALT + password);

}

bool appData::shouldInitialize() {
    return fs::isDirEmpty(appData::resourcesDirLocation() + "safe");
}

//QString
