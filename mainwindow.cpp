#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->listWidget->addItem("");
}

MainWindow::~MainWindow()
{
    delete ui;
}
