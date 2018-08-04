#include <QSet>
#include <QUuid>
#include "slave_item.h"

SlaveItem::SlaveItem(QUuid const &id, SlaveItem &parent)
    : _parent{ &parent }
    , _id{ id }
{
}

int SlaveItem::childPos(QUuid const &child) const
{
    auto const it = std::find_if(_children.cbegin(), _children.cend(), [&child](auto const &item){ return item->id() == child; });
    return it == _children.cend() ? 0 : std::distance(_children.cbegin(), it);
}

int SlaveItem::childPos(SlaveItem const &child) const
{
    return childPos(child.id());
}

int SlaveItem::posAmongSiblings() const
{
    return _parent ? _parent->childPos(*this) : 0;
}

void SlaveItem::append(QUuid const &id)
{
    _children.push_back(new SlaveItem{ id, *this });
}
