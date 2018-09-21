#include "media_player_controller.h"
#include <rtsp_server.h>
#include <config.h>
#include <QDebug>

MediaPlayerController::MediaPlayerController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithoutActivity{ config, plugin, corebus }
{
}

void MediaPlayerController::onSetup(Slave const &slave)
{
    Q_UNUSED(slave)
}
