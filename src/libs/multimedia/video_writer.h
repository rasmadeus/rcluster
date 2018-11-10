#ifndef VIDEO_WRITER_H
#define VIDEO_WRITER_H

#include "gst_element_holder.h"
#include <memory>
#include <device_writer.h>
#include "multimedia_global.h"

class MULTIMEDIA_SHARED_EXPORT VideoWriter : public DeviceWriter
{
    Q_OBJECT

public:
    explicit VideoWriter(QObject *parent = nullptr);
    ~VideoWriter() override { stop(); }

public:
    void start(QVariantHash const &params) override;
    void stop() final override;
    void write([[maybe_unused]] QVariantHash const &data) override {}
    QString path() const override { return QStringLiteral("%1/video_%2.mp4").arg(_dir).arg(_device.toString()); }

public:
    gboolean onBusMessage(GstMessage *message);

private:
    GstBus *_bus{ nullptr };
    std::unique_ptr<GstElementHolder> _pipeline;
};

#endif // VIDEO_WRITER_H
