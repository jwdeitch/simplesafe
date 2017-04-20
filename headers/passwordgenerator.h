#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QWidget>
#include <QString>

namespace Ui {
class passwordgenerator;
}

class passwordgenerator : public QWidget
{
    Q_OBJECT

public:
    explicit passwordgenerator(QWidget *parent = 0);
    void generate();
    ~passwordgenerator();

private slots:
    void on_refreshBtn_clicked();

private:
    Ui::passwordgenerator *ui;
};

#endif // PASSWORDGENERATOR_H
