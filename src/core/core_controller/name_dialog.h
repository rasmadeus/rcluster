#ifndef NAME_DIALOG_H
#define NAME_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class NameDialog : public QDialog
{
    Q_OBJECT

public:
    static QString getName(QString const &name, QWidget &parent);

public:
    explicit NameDialog(QString const &name, QWidget &parent);

public:
    QString name() const { return _name.text(); }

private:
    QLineEdit _name;
    QPushButton _ok;
    QPushButton _cancel;
};

#endif // NAME_DIALOG_H
