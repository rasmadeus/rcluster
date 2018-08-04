#ifndef SLAVE_ITEM_H
#define SLAVE_ITEM_H

#include <QMetaType>
#include <QUuid>
#include <QVariant>
#include <QVector>
#include "widgets_global.h"

class WIDGETS_SHARED_EXPORT SlaveItem
{
public:
    SlaveItem() = default;
    SlaveItem(QUuid const &id, SlaveItem &parent);
    ~SlaveItem() { qDeleteAll(_children); }

public:
    SlaveItem *parent() const { return _parent; }
    void setParent(SlaveItem &slaveItem) { _parent = &slaveItem; }

    QUuid const &id() const { return _id; }
    void setId(QUuid const &id) { _id = id; }

    int childCount() const { return _children.count(); }
    bool isChildless() const { return _children.isEmpty(); }
    bool hasChild(int i) const { return i >= 0 && i < _children.size(); }
    SlaveItem &child(int i) { return *_children[i]; }
    SlaveItem const &child(int i) const { return *_children[i]; }
    SlaveItem &lastChild() { return *_children.last(); }

    int childPos(QUuid const &id) const;
    int childPos(SlaveItem const &item) const;
    int posAmongSiblings() const;

    void clear() { _children.clear(); }
    void append(QUuid const &id);
    void remove(int i) { delete _children.takeAt(i); }

    void setCheckState(Qt::CheckState state) { _checkState = state; }
    Qt::CheckState checkState() const { return _checkState; }
    void toggleCheckState() { _checkState = _checkState == Qt::Checked ? Qt::Unchecked : Qt::Checked; }

protected:
    SlaveItem *_parent{ nullptr };
    QUuid _id;
    QVector<SlaveItem*> _children;
    Qt::CheckState _checkState{ Qt::Unchecked };
};

#endif // SLAVE_ITEM_H
