#ifndef CONTROLLER_WITHOUT_ACTIVITY_H
#define CONTROLLER_WITHOUT_ACTIVITY_H

#include "node_controller.h"

class PLUGIN_SHARED_EXPORT ControllerWithoutActivity : public QObject, public NodeController
{
    Q_OBJECT

public:
    explicit ControllerWithoutActivity(Config const &config, Plugin const &plugin, Corebus &corebus);
};

#endif // CONTROLLER_WITHOUT_ACTIVITY_H
