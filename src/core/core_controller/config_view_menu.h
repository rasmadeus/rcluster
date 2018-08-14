#ifndef CONFIG_VIEW_MENU_H
#define CONFIG_VIEW_MENU_H

#include <QObject>
#include "name_dialog.h"

class Config;
class Plugins;
class Corebus;

class ConfigViewMenu : public QObject
{
    Q_OBJECT

public:
    explicit ConfigViewMenu(Config &config, Plugins &plugins, Corebus &corebus, QWidget &parent);

public:
    void watch(QMenu &menu, QUuid const &id);

private:
    void appendSlave(QUuid const &parent, QString const &type);
    void removeSlave(QUuid const &id);
    void renameSlave(QUuid const &id);
    void enableSlave(QUuid const &id);
    void disableSlave(QUuid const &id);

private:
    QWidget &_parent;
    Config &_config;
    Plugins &_plugins;
    Corebus &_corebus;
};

#endif // CONFIG_VIEW_MENU_H
