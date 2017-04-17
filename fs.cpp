#include "fs.h"

fs::fs()
{

}

bool fs::isDirEmpty(QString dir) {

    return QDir(dir).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0;

}
