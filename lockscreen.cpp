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

void lockScreen::on_pushButton_clicked()
{
    if (ui->password1->text() == ui->password2->text()) {
        appData::setMasterPassword(ui->password1->text());
    }
}
