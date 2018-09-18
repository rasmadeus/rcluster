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
    QVariant dataDisplay(QModelIndex const &index) const;
    QVariant dataDecoration(QModelIndex const &index) const;
};

#endif // DEVICE_MODEL_H
