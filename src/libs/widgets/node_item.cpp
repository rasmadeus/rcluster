#include <QSet>
#include <QUuid>
#include "node_item.h"

NodeItem::NodeItem(QUuid const &id, NodeItem &parent)
    : _parent{ &parent }
    , _id{ id }
{
}

int NodeItem::childPos(QUuid const &child) const
{
    auto const it = std::find_if(_children.cbegin(), _children.cend(), [&child](auto const &item){ return item->id() == child; });
    return it == _children.cend() ? 0 : std::distance(_children.cbegin(), it);
}

int NodeItem::childPos(NodeItem const &child) const
{
    return childPos(child.id());
}

int NodeItem::posAmongSiblings() const
{
    return _parent ? _parent->childPos(*this) : 0;
}

void NodeItem::append(QUuid const &id)
{
    _children.push_back(new NodeItem{ id, *this });
}
