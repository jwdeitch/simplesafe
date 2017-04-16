#ifndef SAFEITEM_H
#define SAFEITEM_H

#include <QWidget>

namespace Ui {
class safeitem;
}

class safeitem : public QWidget
{
    Q_OBJECT

public:
    explicit safeitem(QWidget *parent = 0);
    ~safeitem();

private:
    Ui::safeitem *ui;
};

#endif // SAFEITEM_H
