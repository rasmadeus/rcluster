#ifndef SLAVE_PARAMS_VIEW_H
#define SLAVE_PARAMS_VIEW_H

#include <QStackedWidget>
#include "slave_editor.h"
#include "empty_slave_editor.h"

class SlaveParamsView : public QWidget
{
    Q_OBJECT

public:
    explicit SlaveParamsView(Config &config, Plugins &plugins, Corebus &corebus, QWidget &parent);
    
public:
    void select(QUuid const &id);

private:
    bool hasEditor(QUuid const &id) const;

private:
    Config &_config;
    Plugins &_plugins;
    QStackedWidget _stackedWidget;
    SlaveEditor _slaveEditor;
    EmptySlaveEditor _emptySlaveEditor;
};

#endif // SLAVE_PARAMS_VIEW_H
