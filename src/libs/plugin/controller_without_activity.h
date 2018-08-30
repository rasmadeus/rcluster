#ifndef CONTROLLER_WITHOUT_ACTIVITY_H
#define CONTROLLER_WITHOUT_ACTIVITY_H

#include <QWidget>
#include "slave_controller.h"

class PLUGIN_SHARED_EXPORT ControllerWithoutActivity : public QWidget, public SlaveController
{
    Q_OBJECT

public:
    explicit ControllerWithoutActivity();

public:
    void onInit() override {}

private:
    void catchWmExitGeneratedBySupervistor();
};

#endif // CONTROLLER_WITHOUT_ACTIVITY_H
