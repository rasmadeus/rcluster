#ifndef MEDIA_PLAYER_CONTROLLER_H
#define MEDIA_PLAYER_CONTROLLER_H

#include <controller_without_activity.h>

class MediaPlayerController : public ControllerWithoutActivity
{
    Q_OBJECT

public:
    explicit MediaPlayerController(Config const &config, Plugin const &plugin, Corebus &corebus);

public:
    void onSetup(Slave const &slave) override;
};

#endif // MEDIA_PLAYER_CONTROLLER_H
