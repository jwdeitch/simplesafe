#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QClipboard>
#include <QTimer>
#include <QKeyEvent>
#include <QStandardPaths>
#include "headers/safeitem.h"
#include "headers/appdata.h"
#include <QStringList>
#include <QVector>
#include <QDebug>
#include "headers/passwordgenerator.h"

class QListWidgetItem;
namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setMasterPassword(QString password);
    bool isLocked();
    void copyToClipboard(QString text);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    QString generate();

private slots:
    void on_newAssetBtn_clicked();
    void on_masterPassword_returnPressed();
    void on_createNewLoginBtn_clicked();
    void refreshListView();
    void on_inputPassPeek_pressed();
    void resetClipboardText();
    void on_inputPassPeek_released();
    void showGenerator();
    void on_openGeneratorNewBtn_clicked();
    void on_closeNewPwPanel_clicked();
    void on_openGeneratorBtn_clicked();
    void on_refreshBtn_clicked();
    void on_CopyBtn_clicked();

    void on_searchField_textChanged(const QString &arg1);

    void on_newlogintitletxt_textChanged(const QString &arg1);

    void on_newpasswordtxt_textChanged(const QString &arg1);

    void on_newpasswordtxt_returnPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
