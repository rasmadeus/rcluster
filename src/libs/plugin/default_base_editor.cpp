#include <QSet>
#include <QUuid>
#include "default_base_editor.h"

DefaultBaseEditor::DefaultBaseEditor(const EditorData &data, QWidget &parent)
    : Editor{ data, parent }
{
}

QVariantHash DefaultBaseEditor::params() const
{
    return {};
}

void DefaultBaseEditor::setParams([[maybe_unused]] QVariantHash const &params)
{
}

QStringList DefaultBaseEditor::errors() const
{
    return {};
}
