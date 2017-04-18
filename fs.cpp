#include "fs.h"
#include <QDebug>
fs::fs()
{

}

QStringList fs::readDir(QString path) {
    QDir recoredDir(path);
    return recoredDir.entryList(QDir::NoDotAndDotDot | QDir::Files);
}

bool fs::isDirEmpty(QString dir) {
    return QDir(dir).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries|QDir::Hidden).count() == 0;
}

void fs::writeFile(QString path, QString content) {
    QString filename = path + ".enc";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << content;
    }
    file.close();
}

QString fs::readFile(QString path) {
    QFile file(path);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageLogger(__FILE__, __LINE__, 0).debug() << "Can't open file";
    }
    QTextStream in(&file);
    return in.readAll();
}
