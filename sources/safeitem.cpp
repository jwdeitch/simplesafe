#include "headers/safeitem.h"
#include "ui_safeitem.h"

safeitem::safeitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::safeitem)
{
    ui->setupUi(this);
    ui->copiedLabelMain->setVisible(false);
    ui->typeLabel->fontMetrics().width(ui->typeLabel->text());
#ifdef Q_OS_LINUX
    QFont font = ui->typeLabel->font();
    font.setPixelSize(12);
    ui->typeLabel->setFont(font);
    ui->TitleLabel->setFont(font);
#endif
}

void safeitem::setLabel(QString text) {
    ui->TitleLabel->setText(text);
    label = text;
}

void safeitem::setProperties(QJsonObject jsonObj) {
    label = jsonObj["label"].toString();
    login = jsonObj["login"].toString();
    password = jsonObj["password"].toString();
    setLabel(label);
}

QString safeitem::getLabel() {
    return label;
}

void safeitem::setFilename(QString text) {
    filename = text;
}

void safeitem::flashCopiedLabel() {
    ui->copiedLabelMain->setVisible(true);
    QTimer::singleShot(1000, [this]() { ui->copiedLabelMain->setVisible(false); } );
}

QString safeitem::getLogin() {
    return login;
}

QString safeitem::getPassword() {
    return password;
}

QString safeitem::getFilename() {
    return filename;
}

void safeitem::setLogin(QString text) {
    login = text;
}

void safeitem::setPassword(QString text) {
    password = text;
}

safeitem::~safeitem()
{
    delete ui;
}
