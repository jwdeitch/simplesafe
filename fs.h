#ifndef FS_H
#define FS_H

#include <QDir>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>

class fs
{
public:
    fs();
    static bool isDirEmpty(QString dir);
    static void writeFile(QString path, QString content);
    static QStringList readDir(QString path);
};

#endif // FS_H
