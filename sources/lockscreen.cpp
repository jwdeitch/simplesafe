#include "lockscreen.h"
#include "ui_lockscreen.h"

#include <QString>
#include <QDebug>
#include "appdata.h"

lockScreen::lockScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lockScreen)
{
    ui->setupUi(this);
}

lockScreen::~lockScreen()
{
    delete ui;
}

void lockScreen::on_submitBtn_clicked()
{
    if (ui->password1->text() == ui->password2->text()) {
        appData *ad = new appData(ui->password1->text());
        ad->setMasterPassword(ui->password1->text());
        hide();
        MainWindow *w = new MainWindow();
        w->setMasterPassword(ui->password1->text());
        w->show();
    }
}

void is_password(bool password) {



}
