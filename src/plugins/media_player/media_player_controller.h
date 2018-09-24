#ifndef MEDIA_PLAYER_CONTROLLER_H
#define MEDIA_PLAYER_CONTROLLER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <controller_without_activity.h>

class MediaPlayerController : public ControllerWithoutActivity
{
    Q_OBJECT

public:
    explicit MediaPlayerController(Config const &config, Plugin const &plugin, Corebus &corebus);

public:
    void onSetup(Slave const &slave) override;

private:
    void onStart(Message const &message);
    void onStop(Message const &message);

    void onPlayerStateChanged(QMediaPlayer::State state);
    void start();
    void stop();

private:
    QMediaPlayer _player;
    QMediaPlaylist _playList;
    QVideoWidget _videoWidget;
    QUuid _requestId;
    QUuid _requestSlaveId;
};

#endif // MEDIA_PLAYER_CONTROLLER_H
