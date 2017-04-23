#include "headers/appdata.h"

#include <QDebug>

appData::appData(QString password) {
    BotanWrapper botan;
    botan.setSalt(constants::SALT);
    botan.setPassword(password);
}

QString appData::insertNewPassword(QString label, QString login, QString password, QString filename) {
    auto data = QJsonObject(
    {
        qMakePair(QString("label"), QJsonValue(label)),
        qMakePair(QString("login"), QJsonValue(login)),
        qMakePair(QString("password"), QJsonValue(password))
    });
    QJsonDocument doc(data);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    QString fileString;
    if (filename.isNull()) {
        fileString = QString::number((QDateTime::currentMSecsSinceEpoch()/1000)) + ".p";
    } else {
        fileString = filename;
    }
    fs::writeFile(appData::resourcesDirLocation() + fileString, botan.Encrypt(strJson));
    return filename;
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

void appData::writeSettings(int cbReset, int lockReset) {
    auto data = QJsonObject(
    {
        qMakePair(QString("cbReset"), QJsonValue(cbReset)),
        qMakePair(QString("lockReset"), QJsonValue(lockReset))
    });
    QJsonDocument doc(data);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    fs::writeFile(appData::resourcesDirLocation() + ".settings", botan.Encrypt(strJson));
}

QJsonObject appData::readSettings() {
    QString fileContents = fs::readFile(appData::resourcesDirLocation() + ".settings.enc");
    QString decrpytedContents = botan.Decrypt(fileContents);
    QJsonDocument unencrpytedFile = QJsonDocument::fromJson(decrpytedContents.toUtf8());
    return unencrpytedFile.object();
}

bool appData::doSettingsExist() {
    QFileInfo settings(appData::resourcesDirLocation() + ".settings.enc");
    return settings.exists();
}
