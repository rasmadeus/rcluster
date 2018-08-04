#include <QFormLayout>
#include <config.h>
#include <globals.h>
#include "computer_editor.h"

ComputerEditor::ComputerEditor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent)
    : DefaultBaseEditor{ config, plugins, socket, id, parent }
{
    auto mainLayout = new QFormLayout{ this };
    mainLayout->setMargin(0);
    mainLayout->setSpacing(rcluster::layoutGap());
    mainLayout->addRow(tr("Computer IP:"), &_ip);
}

QVariantHash ComputerEditor::params() const
{
    return {
        { QStringLiteral("ip"), _ip.text() },
    };
}

void ComputerEditor::setParams(QVariantHash const &params)
{
    _ip.setText(params.value(QStringLiteral("ip")).toString());
}
