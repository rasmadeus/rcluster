#ifndef DEVICE_PROXY_MODEL_H
#define DEVICE_PROXY_MODEL_H

#include "node_type_proxy_model.h"

class WIDGETS_SHARED_EXPORT DeviceProxyModel : public NodeTypeProxyModel
{
    Q_OBJECT

public:
    explicit DeviceProxyModel(QObject &parent);
};

#endif // DEVICE_PROXY_MODEL_H
