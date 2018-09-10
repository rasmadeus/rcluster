#include "editor_data.h"

EditorData::EditorData(QUuid const &id, Config const &config, Plugins const &plugins, Corebus &corebus)
    : id{ id }
    , config{ config }
    , plugins{ plugins }
    , corebus{ corebus }
{
}
