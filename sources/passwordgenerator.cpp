#include "headers/passwordgenerator.h"
#include "ui_passwordgenerator.h"
#include <QDebug>
#include <headers/mainwindow.h>

passwordgenerator::passwordgenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::passwordgenerator)
{
    ui->setupUi(this);
    ui->PasswordBox->setAlignment(Qt::AlignCenter);
    generate();
}

QString passwordgenerator::generate() {
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const QString possibleSymbols("!@#$%^&*()_+/][{}><,.|");

    int randAlphaLength = ui->alphaNumSpin->value();
    int randSymbolLength = ui->SymbolSpin->value();

    QString randomAlpha;
    for (int i = 0; i < randAlphaLength; ++i) {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomAlpha.append(nextChar);
    }

    QString randomSymbols;
    for (int i = 0; i < randSymbolLength; ++i) {
        int index = qrand() % possibleSymbols.length();
        QChar nextChar = possibleSymbols.at(index);
        randomSymbols.append(nextChar);
    }

    QString randomStr = randomAlpha + randomSymbols;

    std::random_shuffle(std::begin(randomStr), std::end(randomStr));

    return randomStr;
}

passwordgenerator::~passwordgenerator()
{
    delete ui;
}

void passwordgenerator::on_refreshBtn_clicked()
{
    ui->PasswordBox->clear();

    QString randomStr = generate();

    ui->PasswordBox->insertHtml("<br>");
    ui->PasswordBox->insertPlainText(randomStr);
    ui->PasswordBox->setAlignment(Qt::AlignCenter);
}

void passwordgenerator::on_CopyBtn_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->copyToClipboard(ui->PasswordBox->toPlainText().simplified());
}
