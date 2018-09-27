#include <simplecrypt.h>
#include "pass_line_edit.h"

PassLineEdit::PassLineEdit(QWidget *parent)
    : QLineEdit{ parent }
{
    setEchoMode(PasswordEchoOnEdit);
}

void PassLineEdit::setPassword(QString const &cyphertext)
{
    setText(SimpleCrypt{}.decryptToString(cyphertext));
}

QString PassLineEdit::password() const
{
    return SimpleCrypt{}.encryptToString(text());
}
