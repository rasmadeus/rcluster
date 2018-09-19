#include <QCameraInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <core_bus.h>
#include <message.h>
#include "computer_controller.h"

ComputerController::ComputerController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithoutActivity{ config, plugin, corebus }
{
    _router.handle(QStringLiteral("GET_CAMERAS"), std::bind(&ComputerController::onGetCameras, this, std::placeholders::_1));
}

void ComputerController::onGetCameras(Message const &message)
{
    QJsonArray cameras;
    auto const availableCameras = QCameraInfo::availableCameras();
    for(int i = 0; i < availableCameras.size(); ++i)
    {
        cameras << QJsonObject{
            { QStringLiteral("name"), availableCameras[i].deviceName() },
            { QStringLiteral("desc"), availableCameras[i].description() },
            { QStringLiteral("device_index"), i },
        };
    }

    _corebus.send(QStringLiteral("CAMERAS"), message.from(), { { QStringLiteral("cameras"), std::move(cameras) }, });
}
