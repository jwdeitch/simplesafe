#ifndef FS_H
#define FS_H

#include <QDir>
#include <QString>
class fs
{
public:
    fs();
    static bool isDirEmpty(QString dir);
};

#endif // FS_H
