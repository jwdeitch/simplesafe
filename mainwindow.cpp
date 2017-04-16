#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->newAssetFrame->setVisible(false);
    ui->listWidget->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->listWidget->addItem("");

    QStandardPaths::locate(QStandardPaths::AppDataLocation, QString(), QStandardPaths::LocateDirectory);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newAssetBtn_clicked()
{
    ui->newAssetFrame->setVisible(true);
}
