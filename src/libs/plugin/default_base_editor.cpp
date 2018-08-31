#include <QSet>
#include <QUuid>
#include "default_base_editor.h"

DefaultBaseEditor::DefaultBaseEditor(QWidget &parent)
    : Editor{ parent }
{
}

void DefaultBaseEditor::init()
{
}

SlaveAsParams DefaultBaseEditor::slaveAsParams() const
{
    return {};
}

void DefaultBaseEditor::setSlaveAsParams(SlaveAsParams const &slaveAsParams)
{
    Q_UNUSED(slaveAsParams)
}

QVariantHash DefaultBaseEditor::params() const
{
    return {};
}

void DefaultBaseEditor::setParams(QVariantHash const &params)
{
    Q_UNUSED(params)
}

QStringList DefaultBaseEditor::errors() const
{
    return {};
}
