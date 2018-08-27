#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <QObject>
#include <slave_controller.h>

class CameraController : public QObject, public SlaveController
{
    Q_OBJECT

public:
    explicit CameraController();

public:
    void init() override {}
    void onSetup(Slave const &slave) override;

private:
    void onUpdate(QUuid const &id);
};

#endif // CAMERA_CONTROLLER_H
