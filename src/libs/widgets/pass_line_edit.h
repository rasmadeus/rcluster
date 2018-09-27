#ifndef PASS_LINE_EDIT_H
#define PASS_LINE_EDIT_H

#include <QLineEdit>
#include "widgets_global.h"

class WIDGETS_SHARED_EXPORT PassLineEdit : public QLineEdit
{
public:
    explicit PassLineEdit(QWidget *parent = nullptr);

public:
    void setPassword(QString const &cyphertext);
    QString password() const;
};

#endif // PASS_LINE_EDIT_H
