#ifndef DEVICE_MODEL_H
#define DEVICE_MODEL_H

#include <slave_item_model.h>

class DeviceModel : public SlaveItemModel
{
    Q_OBJECT

public:
    enum
    {
        ColumnInfo = ColumnCaption + 1,
        ColumnState,
        ColumnSize,
    };

public:
    explicit DeviceModel(Config const &config, Plugins const &plugins, QObject &parent);

public:
    int columnCount(QModelIndex const &parent = {}) const override;
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;

public:
    void onSetup(Slave const &slave);

private:
    void onSlaveUpdated(QUuid const &id);

private:
    QVariant dataInfo(QModelIndex const &index, int role) const;
    QVariant dataState(QModelIndex const &index, int role) const;
};

#endif // DEVICE_MODEL_H
