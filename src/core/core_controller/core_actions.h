#ifndef CORE_ACTIONS_H
#define CORE_ACTIONS_H

#include <actions.h>
#include <core_connect_widget.h>

class Corebus;

class CoreActions : public Actions
{
    Q_OBJECT

public:
    explicit CoreActions(Corebus &corebus, QMainWindow &parent);

private:
    void exitCoreAndSlaves();

private:
    Corebus &_corebus;
    CoreConnectWidget _coreConnectWidget;
};

#endif // CORE_ACTIONS_H
