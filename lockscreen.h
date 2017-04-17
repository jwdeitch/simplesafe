#ifndef LOCKSCREEN_H
#define LOCKSCREEN_H

#include <QDialog>
#include "appdata.h"
#include <QString>

namespace Ui {
class lockScreen;
}

class lockScreen : public QDialog
{
    Q_OBJECT

public:
    explicit lockScreen(QWidget *parent = 0);
    ~lockScreen();

private slots:
    void on_submitBtn_clicked();

private:
    Ui::lockScreen *ui;
};

#endif // LOCKSCREEN_H
