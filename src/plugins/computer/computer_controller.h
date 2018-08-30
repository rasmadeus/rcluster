#ifndef COMPUTER_CONTROLLER_H
#define COMPUTER_CONTROLLER_H

#include <slave_controller.h>
#include <controller_without_activity.h>
#include <message_router.h>

class ComputerController : public ControllerWithoutActivity
{
    Q_OBJECT

public:
    ComputerController();

public:
    void onInit() override;
    void onSetup(Slave const &slave) override { Q_UNUSED(slave) }

private:
    void onGetCameras(Message const &message);
};

#endif // COMPUTER_CONTROLLER_H
