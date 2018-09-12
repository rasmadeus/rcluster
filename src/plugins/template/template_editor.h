#ifndef TEMPLATE_EDITOR_H
#define TEMPLATE_EDITOR_H

#include <QTableView>
#include <default_base_editor.h>

class TemplateEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit TemplateEditor(EditorData const &data, QWidget &parent);
};

#endif // TEMPLATE_EDITOR_H
