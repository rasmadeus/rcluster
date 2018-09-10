#include "editor.h"

Editor::Editor(EditorData const &data, QWidget &parent)
    : QWidget{ &parent }
    , _data{ data }
{
}
