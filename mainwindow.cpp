#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->listWidget->addItem("");

    QStandardPaths::locate(QStandardPaths::AppDataLocation, QString(), QStandardPaths::LocateDirectory);

}

MainWindow::~MainWindow()
{
    delete ui;
}
