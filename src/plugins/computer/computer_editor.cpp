#include <QFormLayout>
#include <config.h>
#include <globals.h>
#include "computer_editor.h"

ComputerEditor::ComputerEditor(EditorData const &data, QWidget &parent)
    : DefaultBaseEditor{ data, parent }
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

QStringList ComputerEditor::errors() const
{
    QStringList errors;
    auto id = _config.findLocalParam(_id, QStringLiteral("ip"), _ip.text());
    if (!id.isNull())
        errors << tr("IP %1 is already in use.").arg(_ip.text());
    return errors;
}
