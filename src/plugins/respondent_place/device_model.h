#ifndef DEVICE_MODEL_H
#define DEVICE_MODEL_H

#include <slave_model_check.h>

class DeviceModel : public SlaveModelCheck
{
    Q_OBJECT

public:
    explicit DeviceModel(Config const &config, Plugins const &plugins, QObject &parent);

public:
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(QModelIndex const &index) const override;

private:
    QStringList const _deviceTypes{ QStringLiteral("CAMERA"), };
};

#endif // DEVICE_MODEL_H
