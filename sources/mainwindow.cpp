#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>
#include "headers/safeitem.h"
#include "headers/appdata.h"
#include <QStringList>
#include <QVector>
#include <QDebug>
#include "headers/passwordgenerator.h"

QString masterpassword = NULL;
QVector<QJsonObject> safeItems;

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(535, 419));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->newpasswordtxt->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->newpasswordtxt->setEchoMode(QLineEdit::Password);
    ui->copiedLabelMain->setVisible(false);
    ui->filePane->setVisible(false);
    ui->viewSelectedPassword->setEchoMode(QLineEdit::Password);
    ui->newAssetFrame->setVisible(false);
    ui->listWidget->setAttribute(Qt::WA_MacShowFocusRect, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newAssetBtn_clicked()
{
    ui->newAssetFrame->setVisible(true);
}

void MainWindow::refreshListView() {
    ui->listWidget->clear();
    QString resourcePath = appData::resourcesDirLocation();
    QStringList dirContents = fs::readDir(resourcePath);
    appData *ap = new appData(masterpassword);
    for (int i = 0; i < dirContents.size(); ++i) {
        QJsonObject safelet = ap->retrievePasswordContents(resourcePath + dirContents[i]);
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(100, 30));
        ui->listWidget->addItem(item);
        safeitem *safeListItem = new safeitem;
        safeListItem->setProperties(safelet);
        ui->listWidget->setItemWidget(item, safeListItem);
    }
}

void MainWindow::on_masterPassword_returnPressed()
{
    appData *ad = new appData(ui->masterPassword->text());
    if (ad->checkMasterPassword(ui->masterPassword->text())) {
        masterpassword = ui->masterPassword->text();
        ui->lockFrame->setVisible(false);
        refreshListView();
    }
}

void MainWindow::on_createNewLoginBtn_clicked()
{
    appData *ap = new appData(masterpassword);
    ap->insertNewPassword(ui->newlogintitletxt->text(), ui->newlogintxt->text(), ui->newpasswordtxt->text());
    refreshListView();
    ui->newAssetFrame->setVisible(false);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    safeitem *si =  qobject_cast<safeitem *>( ui->listWidget->itemWidget(item) );
    ui->selectedNameLabel->setText(si->getLabel());
    ui->selectedLoginLabel->setText(si->getLogin());
    ui->viewSelectedPassword->setText(si->getPassword());
}

void MainWindow::setMasterPassword(QString password) {
    masterpassword = password;
    ui->lockFrame->setVisible(false);
}

bool MainWindow::isLocked() {
    return masterpassword == NULL;
}

void MainWindow::on_inputPassPeek_pressed()
{
    ui->newpasswordtxt->setEchoMode(QLineEdit::Normal);
}

void MainWindow::on_inputPassPeek_released()
{
    ui->newpasswordtxt->setEchoMode(QLineEdit::Password);
}

void MainWindow::on_retrievePassPeek_pressed()
{
    ui->viewSelectedPassword->setEchoMode(QLineEdit::Normal);
}

void MainWindow::on_retrievePassPeek_released()
{
    ui->viewSelectedPassword->setEchoMode(QLineEdit::Password);
}

void MainWindow::copyToClipboard(QString text) {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);
    QTimer::singleShot(45000, this, SLOT(resetClipboardText()));
}

void MainWindow::resetClipboardText() {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText("");
}

void MainWindow::showGenerator() {
    passwordgenerator *pw = new passwordgenerator();
    pw->show();
}

void MainWindow::on_copyToClipboardBtn_clicked()
{
    if (ui->viewSelectedPassword->text().size() > 0) {
        copyToClipboard(ui->viewSelectedPassword->text());
        ui->copiedLabelMain->setVisible(true);
        QTimer::singleShot(1000, [this]() { ui->copiedLabelMain->setVisible(false); } );
    }
}

void MainWindow::on_openGeneratorNewBtn_clicked()
{
    passwordgenerator *pw = new passwordgenerator();
    ui->newpasswordtxt->setText(pw->generate());
    ui->newpasswordtxt->setEchoMode(QLineEdit::Normal);
    QTimer::singleShot(1000, [this]() { ui->newpasswordtxt->setEchoMode(QLineEdit::Password); } );
}

void MainWindow::on_closeNewPwPanel_clicked()
{
    ui->newAssetFrame->setVisible(false);
}

void MainWindow::on_fileSelectBtn_clicked()
{
    ui->filePane->setVisible(true);

    ui->fileSelectBtn->setStyleSheet(
                "background-color: white;border-top: 1px solid gray;border-left: 1px solid gray;border-right: 1px solid gray;border-bottom:none;"
                );
    ui->passwordSelectBtn->setStyleSheet(
                "background-color: #ECEFF1;border-top: 1px solid gray;border-left: 1px solid gray;border-right: 1px solid gray;"
                );
    ui->fileSelectBtn->move(ui->fileSelectBtn->x(), ui->fileSelectBtn->y()+1);
    ui->passwordSelectBtn->move(ui->passwordSelectBtn->x(), ui->passwordSelectBtn->y()-1);
}

void MainWindow::on_passwordSelectBtn_clicked()
{
    ui->filePane->setVisible(false);

    ui->fileSelectBtn->setStyleSheet(
                "background-color: #ECEFF1;border-top: 1px solid gray;border-left: 1px solid gray;border-right: 1px solid gray;"
                );
    ui->passwordSelectBtn->setStyleSheet(
                "background-color: white;border-top: 1px solid gray;border-left: 1px solid gray;border-right: 1px solid gray;border-bottom:none;"
                );
    ui->passwordSelectBtn->move(ui->passwordSelectBtn->x(), ui->passwordSelectBtn->y()+1);
    ui->fileSelectBtn->move(ui->fileSelectBtn->x(), ui->fileSelectBtn->y()-1);
}

void MainWindow::on_fileListWidget_clicked(const QModelIndex &index)
{
    qDebug() << "efwef";
}
