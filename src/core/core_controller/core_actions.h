#ifndef CORE_ACTIONS_H
#define CORE_ACTIONS_H

#include <actions.h>
#include <core_connect_widget.h>

class CoreClientSocket;

class CoreActions : public Actions
{
    Q_OBJECT

public:
    explicit CoreActions(CoreClientSocket &socket, QMainWindow &parent);

private:
    void exitCoreAndSlaves();

private:
    CoreClientSocket &_socket;
    CoreConnectWidget _coreConnectWidget;
};

#endif // CORE_ACTIONS_H
