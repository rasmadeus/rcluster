#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <config.h>
#include <corebus.h>
#include <message.h>
#include "media_player_controller.h"

MediaPlayerController::MediaPlayerController(Config const &config, Plugin const &plugin, Corebus &corebus)
    : ControllerWithoutActivity{ config, plugin, corebus }
    , _player{ this }
    , _playList{ this }
{
    connect(&_player, &QMediaPlayer::stateChanged, this, &MediaPlayerController::onPlayerStateChanged);

    _router.handle(QStringLiteral("START"), std::bind(&MediaPlayerController::onStart, this, std::placeholders::_1));
    _router.handle(QStringLiteral("STOP"), std::bind(&MediaPlayerController::onStop, this, std::placeholders::_1));

    _player.setPlaylist(&_playList);
    _player.setVideoOutput(&_videoWidget);
}

void MediaPlayerController::onSetup(Slave const &slave)
{
    if (_player.state() == QMediaPlayer::PlayingState)
        stop();

    _videoWidget.setGeometry(qApp->desktop()->screen(slave.param(QStringLiteral("display")).toInt())->geometry());
    _playList.clear();

    for(auto const &file : slave.param(QStringLiteral("files")).toStringList())
        _playList.addMedia(QUrl::fromUserInput(file));
}

void MediaPlayerController::onStart(Message const &message)
{
    if (_player.state() == QMediaPlayer::PlayingState)
        stop();

    _requestId = message.param(QStringLiteral("request_id")).toUuid();
    _requestSlaveId = message.fromId();

    start();
}

void MediaPlayerController::onStop(Message const &message)
{
    Q_UNUSED(message)
    stop();
}

void MediaPlayerController::onPlayerStateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState)
    {
        _videoWidget.hide();
        _corebus.send(QStringLiteral("STOPPED"), _requestSlaveId.toString(), { { QStringLiteral("request_id"), _requestId }, });
        _requestId = QUuid{};
        _requestSlaveId = QUuid{};
    }
}

void MediaPlayerController::start()
{
    _videoWidget.showFullScreen();
    _player.play();
}

void MediaPlayerController::stop()
{
    if (_player.state() == QMediaPlayer::PlayingState)
        _player.stop();
}
