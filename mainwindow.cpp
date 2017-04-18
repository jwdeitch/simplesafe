#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>
#include "safeitem.h"
#include "appdata.h"
#include <QStringList>

QString masterpassword;

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->newAssetFrame->setVisible(false);
    ui->listWidget->setAttribute(Qt::WA_MacShowFocusRect, 0);

//    for (int i = 0; i < 20; ++i) {
//        QListWidgetItem *item = new QListWidgetItem;
//        item->setSizeHint(QSize(100, 30));
//        ui->listWidget->addItem(item);
//        ui->listWidget->setItemWidget(item, new safeitem);
//    }

    QStringList test = fs::readDir(appData::resourcesDirLocation());
    for (int i = 0; i < test.size(); ++i) {
        QString fileName = test[i];
        if (fileName == ".cactus.enc") {
            continue;
        }
        if (fileName.endsWith(".p.env")) {

        }
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(100, 30));
        ui->listWidget->addItem(item);
        safeitem *safeListItem = new safeitem;
        safeListItem->setLabel(test[i]);
        ui->listWidget->setItemWidget(item, safeListItem);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newAssetBtn_clicked()
{
    ui->newAssetFrame->setVisible(true);
}

void MainWindow::on_masterPassword_returnPressed()
{
    appData *ad = new appData(ui->masterPassword->text());
    if (ad->checkMasterPassword(ui->masterPassword->text())) {
        masterpassword = ui->masterPassword->text();
        ui->lockFrame->setVisible(false);
    }
}

void MainWindow::on_createNewLoginBtn_clicked()
{
    appData *ap = new appData(masterpassword);
    ap->insertNewPassword(ui->newlogintitletxt->text(), ui->newlogintxt->text(), ui->newpasswordtxt->text());
}
