#include "safeitem.h"
#include "ui_safeitem.h"

safeitem::safeitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::safeitem)
{
    ui->setupUi(this);
}

void safeitem::setLabel(QString text) {
    ui->label->setText(text);
}

safeitem::~safeitem()
{
    delete ui;
}
