#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <slave_controller.h>
#include <message_router.h>

class Controller : public SlaveController
{
public:
    Controller();

public:
    void init() override {}
    void onMessage(Message const &message) override { _router.route(message); }

private:
    void onGetCameras(Message const &message);

private:
    MessageRouter _router;
};

#endif // CONTROLLER_H
