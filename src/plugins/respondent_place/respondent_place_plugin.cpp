#include "respondent_place_editor.h"
#include "respondent_place_plugin.h"

Editor *RespondentPlacePlugin::editor(EditorData const &data, QWidget &parent) const
{
    return new RespondentPlaceEditor{ data, parent };
}
