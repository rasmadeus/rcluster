#include "controller_without_activity.h"

ControllerWithoutActivity::ControllerWithoutActivity()
    : QWidget{}
    , SlaveController{}
{
    catchWmExitGeneratedBySupervistor();
}

void ControllerWithoutActivity::catchWmExitGeneratedBySupervistor()
{
    setGeometry(0, 0, 0, 0);
    show();
}
