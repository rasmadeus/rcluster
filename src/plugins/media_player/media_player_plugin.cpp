#include "media_player_controller.h"
#include "media_player_plugin.h"
#include "media_player_editor.h"

Editor *MediaPlayerPlugin::editor(EditorData const &data, QWidget &parent) const
{
    return new MediaPlayerEditor{ data, parent };
}

std::unique_ptr<SlaveController> MediaPlayerPlugin::controller(Config const &config, Plugin const &plugin, Corebus &corebus) const
{
    return std::make_unique<MediaPlayerController>(config, plugin, corebus);
}
