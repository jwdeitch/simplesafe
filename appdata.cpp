#include "appdata.h"

appData::appData() {}

//void insertNewPassword(QString label, QString login, QString password) {



//}

void appData::setMasterPassword(QString password) {
    BotanWrapper botan;
    botan.setSalt(constants::SALT);
    botan.setPassword(password);
    if (appData::shouldInitialize()) {
        QDir().mkdir(appData::resourcesDirLocation() + "safe");
    }
    fs::writeFile(appData::resourcesDirLocation() + "safe/cactus", botan.Encrypt(password));
}

bool appData::shouldInitialize() {
    return fs::isDirEmpty(appData::resourcesDirLocation() + "safe");
}

//QString
