#include "headers/passwordgenerator.h"
#include "ui_passwordgenerator.h"
#include <QDebug>

passwordgenerator::passwordgenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::passwordgenerator)
{
    ui->setupUi(this);
    ui->PasswordBox->setAlignment(Qt::AlignCenter);
    generate();
}

void passwordgenerator::generate() {
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
    qDebug() << randomStr << " |||| " << randomStr.size();
    ui->PasswordBox->setHtml("<br>");
    ui->PasswordBox->insertPlainText(randomStr);
    ui->PasswordBox->setAlignment(Qt::AlignCenter);
}

passwordgenerator::~passwordgenerator()
{
    delete ui;
}

void passwordgenerator::on_refreshBtn_clicked()
{
    generate();
}

void passwordgenerator::on_CopyBtn_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->PasswordBox->toPlainText().simplified());
    QTimer::singleShot(45000, this, SLOT(clearClipboard()));
}

void passwordgenerator::clearClipboard() {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText("");
}