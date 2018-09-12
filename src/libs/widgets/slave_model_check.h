#ifndef SLAVE_MODEL_CHECK_H
#define SLAVE_MODEL_CHECK_H

#include "slave_model.h"

class WIDGETS_SHARED_EXPORT SlaveModelCheck : public SlaveModel
{
    Q_OBJECT

public:
    enum
    {
        RoleToggleCheckState = RoleItemId + 1,
    };

public:
    explicit SlaveModelCheck(Config const &config, Plugins const &plugins, QObject &parent);

public:
    void setChecked(QSet<QUuid> const &slaves) { setChecked(slaves, _root); }
    QSet<QUuid> checked() const { return checked(_root); }
    void selectAll() { setCheckedState(_root, Qt::Checked); }
    void deselectAll() { setCheckedState(_root, Qt::Unchecked); }

public:
    Qt::ItemFlags flags(QModelIndex const &index) const override;
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, QVariant const &value, int role = Qt::EditRole) override;

private:
    void setChecked(QSet<QUuid> const &slaves, SlaveItem &slaveItem);
    QSet<QUuid> checked(SlaveItem const &slaveItem) const;
    void setCheckedState(SlaveItem &item, Qt::CheckState state);
};

#endif // SLAVE_MODEL_CHECK_H
