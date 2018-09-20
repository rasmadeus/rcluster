#include <device_state.h>
#include <config.h>
#include <slave_item_model.h>
#include <svg.h>
#include "state_delegate.h"

StateDelegate::StateDelegate(Config const &config, QObject &parent)
    : QStyledItemDelegate{ &parent }
    , _config{ config }
{
}

void StateDelegate::paint(QPainter *painter, QStyleOptionViewItem const &option, QModelIndex const &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    static QStringList const deviceTypes{ QStringLiteral("CAMERA") };
    auto const id = index.data(SlaveItemModel::RoleItemId).toUuid();
    auto const slave = _config.slave(id);

    if (!deviceTypes.contains(slave.type()))
        return;

    auto const state = slave.runtimeParam(QStringLiteral("state")).value<DeviceState>();
    auto const resource = state == DeviceState::On ? QStringLiteral("device_on") : QStringLiteral("device_off");
    static auto const border = 6;
    auto const side = std::min(option.rect.width(), option.rect.height()) - border;

    auto imageRect = QRect{ 0, 0, side, side };
    imageRect.moveCenter(option.rect.center());

    auto const icon = rcluster::fromSvg(resource, imageRect.size());
    painter->drawPixmap(imageRect, icon);
}
