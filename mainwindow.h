#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_newAssetBtn_clicked();
    void on_masterPassword_returnPressed();
    void on_createNewLoginBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
