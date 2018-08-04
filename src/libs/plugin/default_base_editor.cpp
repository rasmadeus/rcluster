#include <QSet>
#include <QUuid>
#include "default_base_editor.h"

DefaultBaseEditor::DefaultBaseEditor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent)
    : Editor{ config, plugins, socket, id, parent }
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
