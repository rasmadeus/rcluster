#include <QApplication>
#include <QCameraInfo>
#include <QDesktopWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <corebus.h>
#include <message.h>
#include "computer_controller.h"

namespace
{
    auto displays()
    {
        QJsonArray displays;
        for (int i = 0; i < qApp->desktop()->screenCount(); ++i)
        {
            auto const rect = qApp->desktop()->availableGeometry(i);
            displays << QJsonObject{
                { QStringLiteral("x"), rect.x() },
                { QStringLiteral("y"), rect.y() },
                { QStringLiteral("width"), rect.width() },
                { QStringLiteral("height"), rect.height() },
                { QStringLiteral("display_index"), i },
            };
        }
        return displays;
    }

    auto cameras()
    {
        QJsonArray cameras;
        auto const availableCameras = QCameraInfo::availableCameras();
        for (int i = 0; i < availableCameras.size(); ++i)
        {
            cameras << QJsonObject{
                { QStringLiteral("name"), availableCameras[i].deviceName() },
                { QStringLiteral("desc"), availableCameras[i].description() },
                { QStringLiteral("camera_index"), i },
            };
        }
        return cameras;
    }
}

ComputerController::ComputerController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithoutActivity{ config, plugin, corebus }
{
    _router.handle(QStringLiteral("GET_CAMERAS"), std::bind(&ComputerController::onGetCameras, this, std::placeholders::_1));
    _router.handle(QStringLiteral("GET_DISPLAYS"), std::bind(&ComputerController::onGetDisplays, this, std::placeholders::_1));
}

void ComputerController::onSetup([[maybe_unused]] Node const &node)
{
    _corebus.send(QStringLiteral("RUNTIME"), QStringLiteral("core"), {
        { QStringLiteral("node"), _corebus.id() },
        { QStringLiteral("key"), QStringLiteral("displays") },
        { QStringLiteral("value"), ::displays() },
    });

    _corebus.send(QStringLiteral("RUNTIME"), QStringLiteral("core"), {
        { QStringLiteral("node"), _corebus.id() },
        { QStringLiteral("key"), QStringLiteral("cameras") },
        { QStringLiteral("value"), ::cameras() },
    });
}

void ComputerController::onGetCameras(Message const &message)
{
    _corebus.send(QStringLiteral("CAMERAS"), message.from(), { { QStringLiteral("cameras"), ::cameras() }, });
}

void ComputerController::onGetDisplays(Message const &message)
{
    _corebus.send(QStringLiteral("DISPLAYS"), message.from(), { { QStringLiteral("displays"), ::displays() }, });
}
