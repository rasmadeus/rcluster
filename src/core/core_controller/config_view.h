#ifndef CONFIG_VIEW_H
#define CONFIG_VIEW_H

#include <QMainWindow>
#include <QTreeView>
#include <QWidget>
#include <slave_model.h>
#include <slave_sort_model.h>
#include "config_view_menu.h"

class Plugins;
class CoreClientSocket;

class ConfigView : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigView(Config &config, Plugins &plugins, CoreClientSocket &socket, QWidget &parent);

signals:
    void selected(QUuid const &id);

private:
    void showMenu(QPoint const &pos);
    void select(QModelIndex const &current);
    void selectCurrent();

private:
    QTreeView _view;
    SlaveModel _model;
    SlaveSortModel _sortModel;
    ConfigViewMenu _menuController;
    Config &_config;
    Plugins &_plugins;
    CoreClientSocket &_socket;
};

#endif // CONFIG_VIEW_H
