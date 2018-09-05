#ifndef ACTIVE_DEVICE_H
#define ACTIVE_DEVICE_H

#include <atomic>
#include <memory>
#include <thread>
#include <device.h>

class UTILS_SHARED_EXPORT ActiveDevice : public Device
{
    Q_OBJECT

public:
    explicit ActiveDevice(QObject *parent = nullptr);
    ~ActiveDevice() override;

public:
    void start(QVariantHash const &params) override;
    void stop() override;

protected:
    virtual void run(QVariantHash const &params) = 0;
    bool doStop() const { return _doStop; }

private:
    std::atomic<bool> _doStop{ false };
    std::unique_ptr<std::thread> _thread;
};

#endif // ACTIVE_DEVICE_H
