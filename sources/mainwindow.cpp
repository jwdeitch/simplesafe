#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

QString masterpassword = NULL;
QVector<QString> safeItems;

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(238, 419));
    ui->listWidget->installEventFilter(this);
    ui->newpasswordtxt->installEventFilter(this);
    ui->newlogintitletxt->installEventFilter(this);
    ui->createNewLoginBtn->setDisabled(true);
    ui->searchField->installEventFilter(this);
    ui->generatePasswordPanel->setVisible(false);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->newpasswordtxt->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->newpasswordtxt->setEchoMode(QLineEdit::Password);
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
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(100, 30));
    ui->listWidget->addItem(item);
    safeitem *safeListItem = new safeitem;
    safeListItem->setLabel(ui->newlogintitletxt->text());
    safeListItem->setPassword(ui->newpasswordtxt->text());
    safeListItem->setLogin(ui->newlogintxt->text());
    ui->newlogintitletxt->setText("");
    ui->newpasswordtxt->setText("");
    ui->newlogintxt->setText("");
    ui->listWidget->setItemWidget(item, safeListItem);
    ui->newAssetFrame->setVisible(false);
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

void MainWindow::on_openGeneratorBtn_clicked()
{
    ui->generatePasswordPanel->setVisible(true);
}

void MainWindow::on_searchField_textChanged(const QString &arg1)
{
    if (ui->searchField->text().size() > 0) {
        for(int i = 0; i < ui->listWidget->count(); ++i) {
            safeitem *si = qobject_cast<safeitem *>( ui->listWidget->itemWidget(ui->listWidget->item(i)) );
            if (! si->getLabel().contains(arg1) | si->getLogin().contains(arg1)) {
                ui->listWidget->setRowHidden(i,true);
            }
        }
    } else {
        for(int i = 0; i < ui->listWidget->count(); ++i) {
            ui->listWidget->setRowHidden(i,false);
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->searchField) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Down) {
                ui->listWidget->item(0)->setSelected(true);
                ui->listWidget->setFocus();
            }
        }
    }

    if (obj == ui->listWidget){
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            qDebug() << "key " << keyEvent->key() << "from" << obj;
            if ((keyEvent->key()==Qt::Key_Enter) || (keyEvent->key()==Qt::Key_Return)) {
                safeitem *si =  qobject_cast<safeitem *>( ui->listWidget->itemWidget(ui->listWidget->currentItem()));
                copyToClipboard(si->getPassword());
                si->flashCopiedLabel();
                return QObject::eventFilter(obj, event);
            }

            if (keyEvent->key() < Qt::Key_multiply & keyEvent->key() > Qt::Key_Any) {
                ui->searchField->setFocus();
                ui->searchField->setText(keyEvent->text());
                return QObject::eventFilter(obj, event);
            }

        }
    }
    return QObject::eventFilter(obj, event);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape) {
            ui->newAssetFrame->setVisible(false);
            ui->generatePasswordPanel->setVisible(false);
        }
        if (keyEvent->matches(QKeySequence::New)) {
            ui->newAssetFrame->setVisible(true);
            ui->generatePasswordPanel->setVisible(false);
        }
    }
}


QString MainWindow::generate() {
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const QString possibleSymbols("!@#$%^&*()_+/][{}><,.|");

    int randAlphaLength = ui->alphaNumSpin->value();
    int randSymbolLength = ui->SymbolSpin->value();

    QString randomAlpha;
    for (int i = 0; i < randAlphaLength; ++i) {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomAlpha.append(nextChar);
    }

    QString randomSymbols;
    for (int i = 0; i < randSymbolLength; ++i) {
        int index = qrand() % possibleSymbols.length();
        QChar nextChar = possibleSymbols.at(index);
        randomSymbols.append(nextChar);
    }

    QString randomStr = randomAlpha + randomSymbols;

    std::random_shuffle(std::begin(randomStr), std::end(randomStr));

    return randomStr;
}

void MainWindow::on_refreshBtn_clicked()
{
    ui->PasswordBox->clear();

    QString randomStr = generate();

    ui->PasswordBox->insertHtml("<br>");
    ui->PasswordBox->insertPlainText(randomStr);
    ui->PasswordBox->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_CopyBtn_clicked()
{
    copyToClipboard(ui->PasswordBox->toPlainText().simplified());
}

void MainWindow::on_newlogintitletxt_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) {
        ui->newlogintitletxt->setStyleSheet(
                    "background-color:#FEFDFC; border: 1px solid #E64B5F"
                    );
    } else {
        ui->newlogintitletxt->setStyleSheet(
                    "background-color:#FEFDFC; border: 1px solid #D8D9D9"
                    );
    }

    if ( ui->newpasswordtxt->text().size() > 0 && ui->newlogintitletxt->text().size() > 0 ) {
        ui->createNewLoginBtn->setDisabled(false);
    } else {
        ui->createNewLoginBtn->setDisabled(true);
    }
}

void MainWindow::on_newpasswordtxt_textChanged(const QString &arg1)
{
    qDebug() << "wefwef" << arg1.isEmpty() << arg1;
    if (arg1.isEmpty()) {
        ui->newpasswordtxt->setStyleSheet(
                    "background-color:#FEFDFC; border: 1px solid #E64B5F"
                    );
    } else {
        ui->newpasswordtxt->setStyleSheet(
                    "background-color:#FEFDFC; border: 1px solid #D8D9D9"
                    );
    }
    if (ui->newpasswordtxt->text().size() > 0 && ui->newlogintitletxt->text().size() > 0) {
        ui->createNewLoginBtn->setDisabled(false);
    } else {
        ui->createNewLoginBtn->setDisabled(true);
    }
}
