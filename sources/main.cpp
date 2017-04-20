#include "headers/mainwindow.h"
#include <QApplication>
#include "headers/lockscreen.h"
#include "headers/appdata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (appData::shouldInitialize()) {
        lockScreen l;
        l.show();
        return a.exec();
    } else {
        MainWindow w;
        w.show();
        return a.exec();
    }
}
