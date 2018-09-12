#ifndef RESPONDENT_PLACE_EDITOR_H
#define RESPONDENT_PLACE_EDITOR_H

#include <QTableView>
#include <default_base_editor.h>

class RespondentPlaceEditor : public DefaultBaseEditor
{
    Q_OBJECT

public:
    explicit RespondentPlaceEditor(EditorData const &data, QWidget &parent);
};

#endif // RESPONDENT_PLACE_EDITOR_H
