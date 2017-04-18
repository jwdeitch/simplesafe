#include "appdata.h"

#include <QDebug>

appData::appData(QString password) {
    BotanWrapper botan;
    botan.setSalt(constants::SALT);
    botan.setPassword(password);
}

//void insertNewPassword(QString label, QString login, QString password) {



//}

void appData::setMasterPassword(QString password) {
    if (appData::shouldInitialize()) {
        QDir().mkdir(appData::resourcesDirLocation());
    }
    fs::writeFile(appData::resourcesDirLocation() + ".cactus", botan.Encrypt(password));
}

bool appData::shouldInitialize() {
    return fs::isDirEmpty(appData::resourcesDirLocation());
}

bool appData::checkMasterPassword(QString password) {
    QString enteredPassword = botan.Encrypt(password);
    QString masterPassword = fs::readFile(appData::resourcesDirLocation() + ".cactus.enc");
    qDebug() << enteredPassword << masterPassword;
    if (enteredPassword == masterPassword) {
        return true;
    }

    return false;

}

//QString
