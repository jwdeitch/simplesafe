#ifndef SAFEITEM_H
#define SAFEITEM_H

#include <QWidget>
#include <QString>

namespace Ui {
class safeitem;
}

class safeitem : public QWidget
{
    Q_OBJECT

public:
    explicit safeitem(QWidget *parent = 0);
    void setLabel(QString text);
    ~safeitem();

private:
    Ui::safeitem *ui;
};

#endif // SAFEITEM_H
