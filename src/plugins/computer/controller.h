#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <slave_controller.h>
#include <message_router.h>

class Controller : public SlaveController
{
public:
    Controller();

public:
    void init() override;
    void onSetup(Slave const &slave) override { Q_UNUSED(slave) }

private:
    void onGetCameras(Message const &message);
};

#endif // CONTROLLER_H
