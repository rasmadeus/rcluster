#ifndef SLAVE_ITEM_H
#define SLAVE_ITEM_H

#include <QMetaType>
#include <QUuid>
#include <QVariant>
#include <QVector>
#include "widgets_global.h"

class WIDGETS_SHARED_EXPORT NodeItem
{
public:
    NodeItem() = default;
    NodeItem(QUuid const &id, NodeItem &parent);
    ~NodeItem() { qDeleteAll(_children); }

public:
    NodeItem *parent() const { return _parent; }
    void setParent(NodeItem &nodeItem) { _parent = &nodeItem; }

    QUuid const &id() const { return _id; }
    void setId(QUuid const &id) { _id = id; }

    int childCount() const { return _children.count(); }
    bool isChildless() const { return _children.isEmpty(); }
    bool hasChild(int i) const { return i >= 0 && i < _children.size(); }
    NodeItem &child(int i) { return *_children[i]; }
    NodeItem const &child(int i) const { return *_children[i]; }
    NodeItem &lastChild() { return *_children.last(); }

    int childPos(QUuid const &id) const;
    int childPos(NodeItem const &item) const;
    int posAmongSiblings() const;

    void clear() { _children.clear(); }
    void append(QUuid const &id);
    void remove(int i) { delete _children.takeAt(i); }

    void setCheckState(Qt::CheckState state) { _checkState = state; }
    Qt::CheckState checkState() const { return _checkState; }
    void toggleCheckState() { _checkState = _checkState == Qt::Checked ? Qt::Unchecked : Qt::Checked; }

    void setUserData(QVariant const &data) { _userData = data; }
    QVariant const &userData() const { return _userData; }

protected:
    NodeItem *_parent{ nullptr };
    QUuid _id;
    QVector<NodeItem*> _children;
    Qt::CheckState _checkState{ Qt::Unchecked };
    QVariant _userData;
};

#endif // SLAVE_ITEM_H
