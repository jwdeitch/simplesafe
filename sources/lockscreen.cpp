#include "headers/lockscreen.h"
#include "ui_lockscreen.h"

#include <QString>
#include <QDebug>
#include "headers/appdata.h"

lockScreen::lockScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lockScreen)
{
    ui->setupUi(this);
    ui->password1->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->password1->setEchoMode(QLineEdit::Password);
    ui->password2->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->password2->setEchoMode(QLineEdit::Password);
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

void lockScreen::resetMode() {
    ui->greetingFrame->hide();
}

void lockScreen::on_newUserBtn_clicked()
{
    ui->greetingFrame->setVisible(false);
}
