#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>
#include "safeitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->newAssetFrame->setVisible(false);
    ui->listWidget->setAttribute(Qt::WA_MacShowFocusRect, 0);

    for (int i = 0; i < 20; ++i) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(150, 80));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, new safeitem);
    }

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
