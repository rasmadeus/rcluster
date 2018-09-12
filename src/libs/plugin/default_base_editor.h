#ifndef DEFAULT_BASE_EDITOR_H
#define DEFAULT_BASE_EDITOR_H

#include "editor.h"

class PLUGIN_SHARED_EXPORT DefaultBaseEditor : public Editor
{
public:
    explicit DefaultBaseEditor(EditorData const &data, QWidget &parent);

public:
    QVariantHash params() const override;
    void setParams(QVariantHash const &params) override;

    QStringList errors() const override;
};

#endif // DEFAULT_BASE_EDITOR_H
