#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QClipboard>
#include <QTimer>

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

private slots:
    void on_newAssetBtn_clicked();
    void on_masterPassword_returnPressed();
    void on_createNewLoginBtn_clicked();
    void refreshListView();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_inputPassPeek_pressed();
    void resetClipboardText();
    void on_inputPassPeek_released();
    void showGenerator();
    void on_retrievePassPeek_pressed();
    void on_retrievePassPeek_released();
    void on_copyToClipboardBtn_clicked();
    void on_openGeneratorNewBtn_clicked();

    void on_closeNewPwPanel_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
