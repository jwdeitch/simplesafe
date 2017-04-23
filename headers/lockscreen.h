#ifndef LOCKSCREEN_H
#define LOCKSCREEN_H

#include <QDialog>
#include "appdata.h"
#include <QString>
#include "mainwindow.h"

namespace Ui {
class lockScreen;
}

class lockScreen : public QDialog
{
    Q_OBJECT

public:
    explicit lockScreen(QWidget *parent = 0);
    ~lockScreen();
    void resetMode();

private slots:
    void on_submitBtn_clicked();
    void on_newUserBtn_clicked();

private:
    Ui::lockScreen *ui;
};

#endif // LOCKSCREEN_H
