#include "appdata.h"

#include <QDebug>

appData::appData(QString password) {
    BotanWrapper botan;
    botan.setSalt(constants::SALT);
    botan.setPassword(password);
}

void appData::insertNewPassword(QString label, QString login, QString password) {
    auto data1 = QJsonObject(
    {
        qMakePair(QString("label"), QJsonValue(label)),
        qMakePair(QString("login"), QJsonValue(login)),
        qMakePair(QString("password"), QJsonValue(password))
    });
    QJsonDocument doc(data1);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    fs::writeFile(appData::resourcesDirLocation() + random_string(10) + ".p", botan.Encrypt(strJson));
}

QJsonObject appData::retrievePasswordContents(QString path) {
    QString fileContents = fs::readFile(path);
    QString decrpytedContents = botan.Decrypt(fileContents);
    QJsonDocument unencrpytedFile = QJsonDocument::fromJson(decrpytedContents.toUtf8());
    return unencrpytedFile.object();
}

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
    if (enteredPassword == masterPassword) {
        return true;
    }

    return false;

}

// http://stackoverflow.com/a/12468109
QString appData::random_string( int length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    QString str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

//QString
