#include "editor.h"

Editor::Editor(Config const &config, Plugins const &plugins, CoreClientSocket &socket, QUuid const &id, QWidget &parent)
    : QWidget{ &parent }
    , _config{ config }
    , _plugins{ plugins }
    , _socket{ socket }
    , _id{ id }
{
}
