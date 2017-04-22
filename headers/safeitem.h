#ifndef SAFEITEM_H
#define SAFEITEM_H

#include <QWidget>
#include <QString>
#include <QJsonObject>
#include <QTimer>

namespace Ui {
class safeitem;
}

class safeitem : public QWidget
{
    Q_OBJECT

public:
    explicit safeitem(QWidget *parent = 0);
    void setLabel(QString text);
    void setLogin(QString text);
    void setPassword(QString text);
    void setFilename(QString text);
    void is_password(bool password);
    void flashCopiedLabel();
    void setProperties(QJsonObject jsonObj);
    QString getLabel();
    QString getLogin();
    QString getFilename();
    QString getPassword();
    ~safeitem();

private:
    QString label;
    QString login;
    QString password;
    QString filename;

private:
    Ui::safeitem *ui;
};

#endif // SAFEITEM_H
