#ifndef TEMPLATE_CONTROLLER_H
#define TEMPLATE_CONTROLLER_H

#include <controller_with_activity.h>

class RespondentPlaceController : public ControllerWithActivity
{
    Q_OBJECT

public:
    explicit RespondentPlaceController(Config const &config, Plugin const &plugin, Corebus &corebus);

public:
    void onSetup(Slave const &slave) override;
};

#endif // TEMPLATE_CONTROLLER_H
