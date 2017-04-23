#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

QString masterpassword = QString();
QVector<QString> safeItems;
bool inEditMode = false;
QTimer* lockTimeout;

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(238, 419));
    hideAllFrames();
    loadSettings();
    initLock();
    ui->encFilePath->setPlainText(appData::resourcesDirLocation() + "safe");
    ui->listWidget->installEventFilter(this);
    qApp->installEventFilter(this);
    ui->backBtn->setVisible(false);
    ui->newpasswordtxt->installEventFilter(this);
    ui->newlogintitletxt->installEventFilter(this);
    ui->createNewLoginBtn->setDisabled(true);
    ui->searchField->installEventFilter(this);
    ui->searchField->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->masterPassword->setAttribute(Qt::WA_MacShowFocusRect, 0);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->newpasswordtxt->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->newpasswordtxt->setEchoMode(QLineEdit::Password);
    ui->masterPassword->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->masterPassword->setEchoMode(QLineEdit::Password);
    ui->listWidget->setAttribute(Qt::WA_MacShowFocusRect, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newAssetBtn_clicked()
{
    hideAllFrames();
    ui->newAssetFrame->setVisible(true);
    ui->newlogintitletxt->setFocus();
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
        QString fname = dirContents[i];
        fname.chop(4);
        safeListItem->setFilename(fname);
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
    if (inEditMode) {
        safeitem *si = qobject_cast<safeitem *>( ui->listWidget->itemWidget( ui->listWidget->currentItem() ) );
        si->setLabel(ui->newlogintitletxt->text());
        si->setPassword(ui->newpasswordtxt->text());
        si->setLogin(ui->newlogintxt->text());
        ap->insertNewPassword(ui->newlogintitletxt->text(), ui->newlogintxt->text(), ui->newpasswordtxt->text(), si->getFilename());
    } else {
        QString filename = ap->insertNewPassword(ui->newlogintitletxt->text(), ui->newlogintxt->text(), ui->newpasswordtxt->text());
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(100, 30));
        ui->listWidget->addItem(item);
        safeitem *safeListItem = new safeitem;
        safeListItem->setLabel(ui->newlogintitletxt->text());
        safeListItem->setPassword(ui->newpasswordtxt->text());
        safeListItem->setLogin(ui->newlogintxt->text());
        safeListItem->setFilename(filename);
        ui->listWidget->setItemWidget(item, safeListItem);
    }
    closeEditMode();
    ui->backBtn->setVisible(false);
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
    QTimer::singleShot(ui->cbResetSpin->value(), this, SLOT(resetClipboardText()));
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

void MainWindow::on_openGeneratorBtn_clicked()
{
    ui->backBtn->setVisible(true);
    if (!ui->generatePasswordPanel->isVisible()) {
        ui->refreshBtn->click();
    }
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
    if (event->type() == QEvent::MouseMove) {
        resetLock();
        return QObject::eventFilter(obj, event);
    }

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
            if ((keyEvent->key()==Qt::Key_Enter) || (keyEvent->key()==Qt::Key_Return)) {
                safeitem *si =  qobject_cast<safeitem *>( ui->listWidget->itemWidget(ui->listWidget->currentItem()));
                copyToClipboard(si->getPassword());
                si->flashCopiedLabel();
                return QObject::eventFilter(obj, event);
            }

            if (keyEvent->key() == Qt::Key_Space) {
                openEditMode(qobject_cast<safeitem *>( ui->listWidget->itemWidget(ui->listWidget->currentItem())));
                return QObject::eventFilter(obj, event);
            }

            if (keyEvent->key() == Qt::Key_Up) {
                if (ui->listWidget->item(0)->isSelected()) {
                    ui->listWidget->item(0)->setSelected(false);
                    ui->searchField->setFocus();
                }
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
        if (ui->lockFrame->isVisible()) {
            return;
        }
        if (keyEvent->key() == Qt::Key_Escape) {
            hideAllFrames();
            ui->searchField->setFocus();
            closeEditMode();
        }
        if (keyEvent->matches(QKeySequence::New)) {
            ui->newAssetFrame->setVisible(true);
            ui->newlogintitletxt->setFocus();
            ui->backBtn->setVisible(true);
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

void MainWindow::openEditMode(safeitem *si) {
    inEditMode = true;
    ui->newlogintitletxt->setText(si->getLabel());
    ui->newlogintxt->setText(si->getLogin());
    ui->newpasswordtxt->setText(si->getPassword());
    hideAllFrames();
    ui->newAssetFrame->setVisible(true);
    ui->newlogintitletxt->setFocus();
    ui->createNewLoginBtn->setText("Update");
}

void MainWindow::closeEditMode() {
    inEditMode = false;
    ui->newlogintitletxt->setText("");
    ui->newlogintxt->setText("");
    ui->newpasswordtxt->setText("");
    ui->createNewLoginBtn->setText("Save");
    ui->newpasswordtxt->setStyleSheet(
                "background-color:#FEFDFC; border: 1px solid #D8D9D9"
                );
    ui->newlogintitletxt->setStyleSheet(
                "background-color:#FEFDFC; border: 1px solid #D8D9D9"
                );
    ui->createNewLoginBtn->setDisabled(true);
    ui->listWidget->setFocus();
}

void MainWindow::on_newpasswordtxt_returnPressed()
{
    if (ui->createNewLoginBtn->isEnabled()) {
        ui->createNewLoginBtn->click();
    }
}

void MainWindow::on_openSettingsBtn_clicked()
{
    hideAllFrames();
    ui->backBtn->setVisible(true);
    ui->settingsFrame->setVisible(true);
}

void MainWindow::hideAllFrames() {
    ui->newAssetFrame->setVisible(false);
    ui->generatePasswordPanel->setVisible(false);
    ui->settingsFrame->setVisible(false);
    ui->backBtn->setVisible(false);
}

void MainWindow::on_saveSettingsBtn_clicked()
{
    appData *ad = new appData(masterpassword);
    ad->writeSettings(ui->cbResetSpin->value(), ui->lockSpin->value());
    hideAllFrames();
}

void MainWindow::loadSettings() {
    appData *ad = new appData(masterpassword);
    if (ad->doSettingsExist()){
        QJsonObject settings = ad->readSettings();
        ui->cbResetSpin->setValue(settings["cbReset"].toInt());
        ui->lockSpin->setValue(settings["lockReset"].toInt());
    }
}

void MainWindow::lock() {
    hideAllFrames();
    masterpassword = QString();
    ui->lockFrame->setVisible(true);
}

void MainWindow::resetLock() {
    lockTimeout->start(ui->lockSpin->value() * 60 * 1000);
}

void MainWindow::initLock() {
    lockTimeout = new QTimer(this);
    connect(lockTimeout, SIGNAL(timeout()), this, SLOT(lock()));
    resetLock();
}

void MainWindow::on_backBtn_clicked()
{
    hideAllFrames();
}
