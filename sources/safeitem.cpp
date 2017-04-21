#include "headers/safeitem.h"
#include "ui_safeitem.h"

safeitem::safeitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::safeitem)
{
    ui->setupUi(this);
    ui->typeLabel->fontMetrics().width(ui->typeLabel->text());
}

void safeitem::setLabel(QString text) {
    ui->label->setText(text);
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

QString safeitem::getLogin() {
    return login;
}

QString safeitem::getPassword() {
    return password;
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
