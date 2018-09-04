#include <config.h>
#include <core_bus.h>
#include "camera_controller.h"
#include <QCameraInfo>
#include <video_source.h>

CameraController::CameraController()
    : ControllerWithoutActivity{}
{
}

CameraController::~CameraController()
{
}

void CameraController::onSetup(Slave const &slave)
{
    auto cam = QCameraInfo::availableCameras().first();
    auto const params = QVariantHash{ { QStringLiteral("device_desc"), cam.description() }, };

    _videoSource = std::make_unique<VideoSource>();
    _thread = std::make_unique<QThread>();
    _videoSource->moveToThread(_thread.get());
    connect(this, &CameraController::started, _videoSource.get(), &VideoSource::start);
    connect(_videoSource.get(), &VideoSource::ready, this, &CameraController::onCamReady);
    _thread->start();
    emit started(params);
}

void CameraController::onCamStarted()
{
    qDebug() << "Camera started";
}

void CameraController::onCamStopped()
{
    qDebug() << "Camera stopped";
}

void CameraController::onCamReady()
{
    qDebug() << "Camera ready";
}
