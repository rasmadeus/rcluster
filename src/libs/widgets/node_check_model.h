#ifndef SLAVE_CHECK_MODEL_H
#define SLAVE_CHECK_MODEL_H

#include "node_model.h"

class WIDGETS_SHARED_EXPORT NodeCheckModel : public NodeModel
{
    Q_OBJECT

public:
    enum
    {
        RoleToggleCheckState = RoleItemId + 1,
    };

public:
    explicit NodeCheckModel(Config const &config, Plugins const &plugins, QObject &parent);

public:
    void setChecked(QVariantList const &nodes) { setChecked(nodes, _root); }
    QVariantList checked() const { return checked(_root); }
    void selectAll() { setCheckedState(_root, Qt::Checked); }
    void deselectAll() { setCheckedState(_root, Qt::Unchecked); }

public:
    Qt::ItemFlags flags(QModelIndex const &index) const override;
    QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, QVariant const &value, int role = Qt::EditRole) override;

private:
    void setChecked(QVariantList const &nodes, NodeItem &nodeItem);
    QVariantList checked(NodeItem const &nodeItem) const;
    void setCheckedState(NodeItem &item, Qt::CheckState state);
};

#endif // SLAVE_CHECK_MODEL_H
