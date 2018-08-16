#include <QCameraInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <core_bus.h>
#include <message.h>
#include "controller.h"

Controller::Controller()
    : SlaveController{}
{
}

void Controller::init()
{
    _router.handle(QStringLiteral("GET_CAMERAS"), std::bind(&Controller::onGetCameras, this, std::placeholders::_1));
}

void Controller::onGetCameras(Message const &message)
{
    QJsonArray cameras;
    for(auto const &camera : QCameraInfo::availableCameras())
        cameras << QJsonObject{ { QStringLiteral("name"), camera.deviceName() }, { QStringLiteral("desc"), camera.description() }, };
    _corebus->send(QStringLiteral("CAMERAS"), message.from(), { { QStringLiteral("cameras"), std::move(cameras) }, });
}
