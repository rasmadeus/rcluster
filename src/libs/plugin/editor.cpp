#include "editor.h"

Editor::Editor(EditorData const &data, QWidget &parent)
    : QWidget{ &parent }
    , _id{ data.id }
    , _config{ data.config }
    , _plugins{ data.plugins }
    , _corebus{ data.corebus }
{
}
