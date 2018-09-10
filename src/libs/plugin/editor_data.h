#ifndef EDITOR_DATA_H
#define EDITOR_DATA_H

#include <QUuid>
#include "plugin_global.h"

class Config;
class Corebus;
class Plugins;

struct PLUGIN_SHARED_EXPORT EditorData
{
    EditorData(QUuid const &id, Config const &config, Plugins const &plugins, Corebus &corebus);

    QUuid const id;
    Config const &config;
    Plugins const &plugins;
    Corebus &corebus;
};

#endif // EDITOR_DATA_H
