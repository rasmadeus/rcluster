#ifndef CONFIG_VIEW_H
#define CONFIG_VIEW_H

#include <QMainWindow>
#include <QTreeView>
#include <QWidget>
#include <node_model.h>
#include <node_sort_model.h>
#include "config_view_menu.h"

class Plugins;
class Corebus;

class ConfigView : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigView(Config &config, Plugins &plugins, Corebus &corebus, QWidget &parent);

signals:
    void selected(QUuid const &id);

private:
    void showMenu(QPoint const &pos);
    void select(QModelIndex const &current);
    void sortNodes();
    void trySelectLast(QModelIndex const &parent, int first, int last);

private:
    QTreeView _view;
    NodeModel _model;
    NodeSortModel _sortModel;
    ConfigViewMenu _menuController;
    Config &_config;
    Plugins &_plugins;
    Corebus &_corebus;
};

#endif // CONFIG_VIEW_H
