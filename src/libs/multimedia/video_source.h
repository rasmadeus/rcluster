#ifndef VIDEO_SOURCE_H
#define VIDEO_SOURCE_H

#include <active_device.h>
#include <multimedia_global.h>

class MULTIMEDIA_SHARED_EXPORT VideoSource : public ActiveDevice
{
    Q_OBJECT

public:
    explicit VideoSource(QObject *parent = nullptr);

protected:
    void run(QVariantHash const &params) override;

signals:
    void ready();
};

#endif // VIDEO_SOURCE_H
