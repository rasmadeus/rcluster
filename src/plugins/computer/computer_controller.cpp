#include <QCameraInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <core_bus.h>
#include <message.h>
#include "computer_controller.h"

ComputerController::ComputerController()
    : ControllerWithoutActivity{}
{
}

void ComputerController::onInit()
{
    _router.handle(QStringLiteral("GET_CAMERAS"), std::bind(&ComputerController::onGetCameras, this, std::placeholders::_1));
}

void ComputerController::onGetCameras(Message const &message)
{
    QJsonArray cameras;
    for(auto const &camera : QCameraInfo::availableCameras())
        cameras << QJsonObject{ { QStringLiteral("name"), camera.deviceName() }, { QStringLiteral("desc"), camera.description() }, };
    _corebus->send(QStringLiteral("CAMERAS"), message.from(), { { QStringLiteral("cameras"), std::move(cameras) }, });
}
