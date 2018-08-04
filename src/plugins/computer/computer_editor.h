#ifndef COMPUTER_EDITOR_H
#define COMPUTER_EDITOR_H

#include <QLineEdit>
#include <default_base_editor.h>

class ComputerEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit ComputerEditor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;

private:
    QLineEdit _ip;
};

#endif // COMPUTER_EDITOR_H
