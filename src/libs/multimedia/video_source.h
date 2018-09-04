#ifndef VIDEO_SOURCE_H
#define VIDEO_SOURCE_H

#include <QObject>
#include <device.h>

class VideoSource : public Device
{
    Q_OBJECT

public:
    explicit VideoSource(QObject *parent = nullptr);
    ~VideoSource() override;

public:
    void start(QVariantHash const &params) override;
    void stop() override;

private:
    void run(QVariantHash const &params);

Q_SIGNALS:
    void ready();

private:
    bool _doStop{ false };
};

#endif // VIDEO_SOURCE_H
