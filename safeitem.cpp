#include "safeitem.h"
#include "ui_safeitem.h"

safeitem::safeitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::safeitem)
{
    ui->setupUi(this);
}

safeitem::~safeitem()
{
    delete ui;
}
