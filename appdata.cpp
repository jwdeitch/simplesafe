#include "appdata.h"

appData::appData() {}

//void insertNewPassword(QString label, QString login, QString password) {



//}

void appData::setMasterPassword(QString password) {
    BotanWrapper botan;
    botan.setSalt(constants::SALT);
    botan.setPassword(password);
    fs::writeFile(appData::resourcesDirLocation() + "safe/cactus", botan.Encode(password));
}

bool appData::shouldInitialize() {
    return fs::isDirEmpty(appData::resourcesDirLocation() + "safe");
}

//QString
