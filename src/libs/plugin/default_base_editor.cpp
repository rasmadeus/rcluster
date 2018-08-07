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

QSet<QUuid> DefaultBaseEditor::events() const
{
    return {};
}

void DefaultBaseEditor::setEvents(QSet<QUuid> const &events)
{
    Q_UNUSED(events)
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
