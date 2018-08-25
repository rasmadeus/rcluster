#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <slave_controller.h>

class Controller : public QObject, public SlaveController
{
public:
    Controller();

public:
    void init() override {}
    void onSetup(Slave const &slave) override;

private:
    void onUpdate(QUuid const &id);
};

#endif // CONTROLLER_H
