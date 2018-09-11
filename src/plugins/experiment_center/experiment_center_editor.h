#ifndef EXPERIMENT_CENTER_EDITOR_H
#define EXPERIMENT_CENTER_EDITOR_H

#include <default_base_editor.h>

class ExperimentCenterEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit ExperimentCenterEditor(EditorData const &data, QWidget &parent);

};

#endif // EXPERIMENT_CENTER_EDITOR_H
