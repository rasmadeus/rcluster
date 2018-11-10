#include "device_proxy_model.h"

DeviceProxyModel::DeviceProxyModel(QObject &parent)
    : NodeTypeProxyModel
    {
        { QStringLiteral("COMPUTER"), QStringLiteral("DEVICES"), QStringLiteral("CAMERA"), QStringLiteral("EYE_TRACKER"), },
        { QStringLiteral("CAMERA"), QStringLiteral("EYE_TRACKER") },
        parent
    }
{
}