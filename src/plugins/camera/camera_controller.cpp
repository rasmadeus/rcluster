#include <config.h>
#include <core_bus.h>
#include "camera_controller.h"
#include <QCameraInfo>
#include <video_source.h>

CameraController::CameraController()
    : ControllerWithoutActivity{}
{
    connect(&_videoSource, &VideoSource::started, this, &CameraController::onCamStarted);
    connect(&_videoSource, &VideoSource::stopped, this, &CameraController::onCamStopped);
    connect(&_videoSource, &VideoSource::ready, this, &CameraController::onCamReady);
}

void CameraController::onSetup(Slave const &slave)
{
    _videoSource.start(slave.params());
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
