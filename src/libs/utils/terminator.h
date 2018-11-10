#ifndef TERMINATOR_H
#define TERMINATOR_H

#include "active_device.h"

class UTILS_SHARED_EXPORT Terminator : public ActiveDevice
{
    Q_OBJECT

public:
    explicit Terminator(QObject *parent = nullptr);

protected:
    void run(QVariantHash const &params) override;
};

#endif // ACTIVE_DEVICE_H
